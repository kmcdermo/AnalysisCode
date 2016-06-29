#!/usr/bin/env python

"""Fast but memory hungry alternative to ROOT's hadd.

fhadd - the main routine
createExample - creates an example root file containing a lot (sub)directories
mergeFiles - helper function for ganga's CustomMerger
"""

__author__ = "Sebastian Schmitt"
__contact__ = "sebastian.schmitt@cern.ch"
__version__ = "0.1"

import logging
import shutil
import os

# safe sys.argv for later parsing and hide it from ROOT
import sys
my_sys_argv = sys.argv
sys.argv = []
import ROOT
ROOT.TH1.AddDirectory(False)
sys.argv = my_sys_argv

def readKeys(directory, classname=None):
    """Return a list of objects in directory that inherit from classname. """

    if not directory.InheritsFrom("TDirectory"):
        return []
    return [key.ReadObj() for key in directory.GetListOfKeys() if classname == None or key.ReadObj().InheritsFrom(classname)]

def loop(directory, classname = None):
    """Traverse directory recursively and return a list of (path, name) pairs of
    all objects inheriting from classname."""

    contents = []

    className = classname.split(",");

    for cl in className:
        for d in readKeys(directory):
            
            if not cl or d.InheritsFrom(cl):
                contents.append((directory.GetPath().split(':')[-1], d.GetName()))

            contents += loop(d, cl)

    return contents

def fhadd(target, sources, classname, force=False, verbose=False, slow=False):
    """This function will merge objects from a list of root files and write them
    to a target root file. The target file is newly created and must not
    exist, or if -f ("force") is given, must not be one of the source files.

    IMPORTANT: It is required that all files have the same content!

    Fast but memory hungry alternative to ROOT's hadd.

    Arguments:

    target -- name of the target root file
    sources -- list of source root files
    classname -- restrict merging to objects inheriting from classname
    force -- overwrite target file if exists
    """

    # check if target file exists and exit if it does and not in force mode
    if not force and os.path.exists(target):
        raise RuntimeError("target file %s exists" % target)

    # configure logger
    logger = logging.getLogger("fhadd")
    if verbose:
        logging.basicConfig(level=logging.DEBUG)

    # open the target file
    print "fhadd Target file:", target
    outfile = ROOT.TFile(target, "RECREATE")

    # open the seed file - contents is looked up from here
    seedfilename = sources[0]
    print "fhadd Source file 1", seedfilename
    seedfile = ROOT.TFile(seedfilename)

    # open remaining files
    otherfiles = []
    for n, f in enumerate(sources[1:]):
        print "fhadd Source file %d: %s" % (n+2, f)
        otherfiles.append(ROOT.TFile(f))

    # get contents of seed file
    logger.debug("looping over seed file")
    contents = loop(seedfile, classname)
    logger.debug("done")

    # loop over contents and merge objects from other files to seed file objects
    for n, (path, hname) in enumerate(contents):

        print "fhadd Target object: %s" % os.path.join(path, hname)

        outfile.cd('/')
        ROOT.gDirectory.cd('/')

        obj_path = os.path.join(path, hname)
        obj = seedfile.Get(obj_path[1:])

        # merge objects
        l = ROOT.TList()
        for o in [of.Get(obj_path[1:]) for of in otherfiles]:
            l.Add(o)
        obj.Merge(l)

        # delete objects if in slow mode
        if slow:
            logger.debug("Deleting %d object(s)", l.GetEntries())
            l.Delete()

        # create target directory structure
        for d in path.split('/')[1:]:

            directory = ROOT.gDirectory.GetDirectory(d)

            if not directory:
                ROOT.gDirectory.mkdir(d).cd()
            else:
                ROOT.gDirectory.cd(d)

        # write object to target
        obj.Write(obj.GetName(), ROOT.TObject.kOverwrite)

    logger.debug("Writing and closing file")

    # let ROOT forget about open files - prevents deletion of TKeys
    for f in [outfile, seedfile]+otherfiles:
        ROOT.gROOT.GetListOfFiles().Remove(f);

    outfile.Write()
    outfile.Close()

    return 0

if __name__ == "__main__":

    try:
        import argparse
    except ImportError, exc:
        sys.stderr.write("Error: failed to import argparse module, available from python 2.7 on. (%s)\n" % exc)
        sys.exit()

    parser = argparse.ArgumentParser(description='fhadd - fast hadd')

    parser.add_argument('target', type=str,
                        help='target file')

    parser.add_argument('source', type=str, nargs="+",
                        help='source file(s)')

    parser.add_argument('--classname', dest="classname",
                        help='restrict merging to classname',
                        default="TTree,TH1")

    parser.add_argument('-f', '--force', dest="force",
                        help='allow to overwrite target',
                        default=False,
                        action="store_true")

    parser.add_argument('--slow', dest="slow",
                        help='delete read objects - safes memory but is slower',
                        default=False,
                        action="store_true")

    parser.add_argument('-v', '--verbose', dest="verbose",
                        help='verbose',
                        default=False,
                        action="store_true")

    args = parser.parse_args()

    try:
        fhadd(args.target, args.source, args.classname, args.force, args.verbose, args.slow)
    except KeyboardInterrupt:
        sys.exit()

def createExample(filename, nsub=5, nhists=2, force=False, verbose=False):

    if not force and os.path.exists(filename):
        raise RuntimeError("target file %s exists" % filename)

    # configure logger
    logger = logging.getLogger("createExample")
    if verbose:
        logging.basicConfig(level=logging.DEBUG)

    f = ROOT.TFile(filename, "RECREATE")
    f.SetCompressionLevel(1)

    objs = [ROOT.TH1D("h%d"%i, "h%d"%i, 100, -2, -2) for i in xrange(nhists)]

    ROOT.gRandom = ROOT.TRandom3(0)

    for o in objs:
        for n in xrange(1000):
            o.Fill(ROOT.gRandom.Gaus())

    for a in xrange(nsub):

        logger.debug("/%d", a)
        da = f.mkdir(str(a))
        da.cd()

        for o in objs:
            o.Write()

        for b in xrange(nsub):

            logger.debug("/%d/%d", a, b)
            db = da.mkdir(str(b))
            db.cd()

            for o in objs:
                o.Write()

            for c in xrange(nsub):

                logger.debug("/%d/%d/%d", a, b, c)
                dc = db.mkdir(str(c))
                dc.cd()

                for o in objs:
                    o.Write()

                for d in xrange(nsub):

                    logger.debug("/%d/%d/%d/%d", a, b, c, d)
                    dd = dc.mkdir(str(d))
                    dd.cd()

                    for o in objs:
                        o.Write()

    f.Write()
    f.Close()

def mergefiles(file_list, output_file):
    """ganga CustomMerger helper function.

    http://ganga.web.cern.ch/ganga/release/5.8.5/reports/html/Manuals/CustomMerger.html

    Restrict to histograms, i.e. objects inheriting from TH1.
    """

    status = fhadd(output_file, file_list, classname="TTree,TH1", force=True, verbose=False)

    return status
