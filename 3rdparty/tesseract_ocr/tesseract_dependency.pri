message("-----------------start------------- ")

INCLUDEPATH +=  $$PWD
isEmpty(TESSERACT_DIR) {
    warning("Using Tesseract src dir specified at Qt Creator wizard")
    message("set TESSERACT_DIR as environment variable or qmake variable to get rid of this message")
    TESSERACT_DIR = $$PWD
    message("TESSERACT_DIR: " $$PWD)
}

!isEmpty(TESSERACT_DIR): {
    TESSERACT_SRCDIR = $$TESSERACT_DIR/tesseract
    message("TESSERACT_SRCDIR: " $$TESSERACT_SRCDIR)

}

requires(exists($$TESSERACT_SRCDIR))

!exists($$TESSERACT_DIR):message("No tesseract src dir found - set TESSERACT_DIR to enable.")

LIBS +=  -llept  \

INCLUDEPATH += \
    $$TESSERACT_SRCDIR \
    $$TESSERACT_SRCDIR/include \
    $$TESSERACT_SRCDIR/src/api \
    $$TESSERACT_SRCDIR/src/arch \
    $$TESSERACT_SRCDIR/src/ccmain \
    $$TESSERACT_SRCDIR/src/ccstruct \
    $$TESSERACT_SRCDIR/src/ccutil \
    $$TESSERACT_SRCDIR/src/classify \
    $$TESSERACT_SRCDIR/src/cutil \
    $$TESSERACT_SRCDIR/src/dict \
    $$TESSERACT_SRCDIR/src/lstm \
    $$TESSERACT_SRCDIR/src/opencl \
    $$TESSERACT_SRCDIR/src/textord \
    $$TESSERACT_SRCDIR/src/viewer \
    $$TESSERACT_SRCDIR/src/wordrec \
#    $$TESSERACT_SRCDIR/src/training \
    /usr/include/c++/8 \
    /usr/include/leptonica
HEADERS += $$TESSERACT_SRCDIR/include/tesseract/baseapi.h \
           $$TESSERACT_SRCDIR/include/tesseract/capi.h \
           $$TESSERACT_SRCDIR/include/tesseract/export.h \
           $$TESSERACT_SRCDIR/include/tesseract/ltrresultiterator.h \
           $$TESSERACT_SRCDIR/include/tesseract/ocrclass.h \
           $$TESSERACT_SRCDIR/include/tesseract/osdetect.h \
           $$TESSERACT_SRCDIR/include/tesseract/pageiterator.h \
           $$TESSERACT_SRCDIR/include/tesseract/publictypes.h \
           $$TESSERACT_SRCDIR/include/tesseract/renderer.h \
           $$TESSERACT_SRCDIR/include/tesseract/resultiterator.h \
           $$TESSERACT_SRCDIR/include/tesseract/unichar.h \
          $$TESSERACT_SRCDIR/src/api/pdf_ttf.h \
          $$TESSERACT_SRCDIR/src/arch/dotproduct.h \
          $$TESSERACT_SRCDIR/src/arch/intsimdmatrix.h \
          $$TESSERACT_SRCDIR/src/arch/simddetect.h \
          $$TESSERACT_SRCDIR/src/ccmain/control.h \
          $$TESSERACT_SRCDIR/src/ccmain/docqual.h \
          $$TESSERACT_SRCDIR/src/ccmain/equationdetect.h \
          $$TESSERACT_SRCDIR/src/ccmain/fixspace.h \
          $$TESSERACT_SRCDIR/src/ccmain/mutableiterator.h \
          $$TESSERACT_SRCDIR/src/ccmain/output.h \
          $$TESSERACT_SRCDIR/src/ccmain/paragraphs.h \
          $$TESSERACT_SRCDIR/src/ccmain/paragraphs_internal.h \
          $$TESSERACT_SRCDIR/src/ccmain/paramsd.h \
          $$TESSERACT_SRCDIR/src/ccmain/pgedit.h \
          $$TESSERACT_SRCDIR/src/ccmain/reject.h \
          $$TESSERACT_SRCDIR/src/ccmain/tesseractclass.h \
          $$TESSERACT_SRCDIR/src/ccmain/tessvars.h \
          $$TESSERACT_SRCDIR/src/ccmain/thresholder.h \
          $$TESSERACT_SRCDIR/src/ccmain/werdit.h \
          $$TESSERACT_SRCDIR/src/ccstruct/blamer.h \
          $$TESSERACT_SRCDIR/src/ccstruct/blobbox.h \
          $$TESSERACT_SRCDIR/src/ccstruct/blobs.h \
          $$TESSERACT_SRCDIR/src/ccstruct/blread.h \
          $$TESSERACT_SRCDIR/src/ccstruct/boxread.h \
          $$TESSERACT_SRCDIR/src/ccstruct/boxword.h \
          $$TESSERACT_SRCDIR/src/ccstruct/ccstruct.h \
          $$TESSERACT_SRCDIR/src/ccstruct/coutln.h \
          $$TESSERACT_SRCDIR/src/ccstruct/crakedge.h \
          $$TESSERACT_SRCDIR/src/ccstruct/debugpixa.h \
          $$TESSERACT_SRCDIR/src/ccstruct/detlinefit.h \
          $$TESSERACT_SRCDIR/src/ccstruct/dppoint.h \
          $$TESSERACT_SRCDIR/src/ccstruct/fontinfo.h \
          $$TESSERACT_SRCDIR/src/ccstruct/image.h \
          $$TESSERACT_SRCDIR/src/ccstruct/imagedata.h \
          $$TESSERACT_SRCDIR/src/ccstruct/linlsq.h \
          $$TESSERACT_SRCDIR/src/ccstruct/matrix.h \
          $$TESSERACT_SRCDIR/src/ccstruct/mod128.h \
          $$TESSERACT_SRCDIR/src/ccstruct/normalis.h \
          $$TESSERACT_SRCDIR/src/ccstruct/ocrblock.h \
          $$TESSERACT_SRCDIR/src/ccstruct/ocrpara.h \
          $$TESSERACT_SRCDIR/src/ccstruct/ocrrow.h \
          $$TESSERACT_SRCDIR/src/ccstruct/otsuthr.h \
          $$TESSERACT_SRCDIR/src/ccstruct/pageres.h \
          $$TESSERACT_SRCDIR/src/ccstruct/params_training_featdef.h \
          $$TESSERACT_SRCDIR/src/ccstruct/pdblock.h \
          $$TESSERACT_SRCDIR/src/ccstruct/points.h \
          $$TESSERACT_SRCDIR/src/ccstruct/polyaprx.h \
          $$TESSERACT_SRCDIR/src/ccstruct/polyblk.h \
          $$TESSERACT_SRCDIR/src/ccstruct/quadlsq.h \
          $$TESSERACT_SRCDIR/src/ccstruct/quadratc.h \
          $$TESSERACT_SRCDIR/src/ccstruct/quspline.h \
          $$TESSERACT_SRCDIR/src/ccstruct/ratngs.h \
          $$TESSERACT_SRCDIR/src/ccstruct/rect.h \
          $$TESSERACT_SRCDIR/src/ccstruct/rejctmap.h \
          $$TESSERACT_SRCDIR/src/ccstruct/seam.h \
          $$TESSERACT_SRCDIR/src/ccstruct/split.h \
          $$TESSERACT_SRCDIR/src/ccstruct/statistc.h \
          $$TESSERACT_SRCDIR/src/ccstruct/stepblob.h \
          $$TESSERACT_SRCDIR/src/ccstruct/tabletransfer.h \
          $$TESSERACT_SRCDIR/src/ccstruct/werd.h \
          $$TESSERACT_SRCDIR/src/ccutil/ambigs.h \
          $$TESSERACT_SRCDIR/src/ccutil/bitvector.h \
          $$TESSERACT_SRCDIR/src/ccutil/ccutil.h \
          $$TESSERACT_SRCDIR/src/ccutil/clst.h \
          $$TESSERACT_SRCDIR/src/ccutil/elst.h \
          $$TESSERACT_SRCDIR/src/ccutil/elst2.h \
          $$TESSERACT_SRCDIR/src/ccutil/errcode.h \
          $$TESSERACT_SRCDIR/src/ccutil/fileerr.h \
          $$TESSERACT_SRCDIR/src/ccutil/genericheap.h \
          $$TESSERACT_SRCDIR/src/ccutil/genericvector.h \
          $$TESSERACT_SRCDIR/src/ccutil/helpers.h \
          $$TESSERACT_SRCDIR/src/ccutil/host.h \
          $$TESSERACT_SRCDIR/src/ccutil/indexmapbidi.h \
          $$TESSERACT_SRCDIR/src/ccutil/kdpair.h \
          $$TESSERACT_SRCDIR/src/ccutil/list.h \
          $$TESSERACT_SRCDIR/src/ccutil/lsterr.h \
          $$TESSERACT_SRCDIR/src/ccutil/object_cache.h \
          $$TESSERACT_SRCDIR/src/ccutil/params.h \
          $$TESSERACT_SRCDIR/src/ccutil/qrsequence.h \
          $$TESSERACT_SRCDIR/src/ccutil/scanutils.h \
          $$TESSERACT_SRCDIR/src/ccutil/serialis.h \
          $$TESSERACT_SRCDIR/src/ccutil/sorthelper.h \
          $$TESSERACT_SRCDIR/src/ccutil/tessdatamanager.h \
          $$TESSERACT_SRCDIR/src/ccutil/tprintf.h \
          $$TESSERACT_SRCDIR/src/ccutil/unicharcompress.h \
          $$TESSERACT_SRCDIR/src/ccutil/unicharmap.h \
          $$TESSERACT_SRCDIR/src/ccutil/unicharset.h \
          $$TESSERACT_SRCDIR/src/ccutil/unicity_table.h \
          $$TESSERACT_SRCDIR/src/ccutil/universalambigs.h \
          $$TESSERACT_SRCDIR/src/classify/adaptive.h \
          $$TESSERACT_SRCDIR/src/classify/classify.h \
          $$TESSERACT_SRCDIR/src/classify/cluster.h \
          $$TESSERACT_SRCDIR/src/classify/clusttool.h \
          $$TESSERACT_SRCDIR/src/classify/featdefs.h \
          $$TESSERACT_SRCDIR/src/classify/float2int.h \
          $$TESSERACT_SRCDIR/src/classify/fpoint.h \
          $$TESSERACT_SRCDIR/src/classify/intfeaturespace.h \
          $$TESSERACT_SRCDIR/src/classify/intfx.h \
          $$TESSERACT_SRCDIR/src/classify/intmatcher.h \
          $$TESSERACT_SRCDIR/src/classify/intproto.h \
          $$TESSERACT_SRCDIR/src/classify/kdtree.h \
          $$TESSERACT_SRCDIR/src/classify/mf.h \
          $$TESSERACT_SRCDIR/src/classify/mfdefs.h \
          $$TESSERACT_SRCDIR/src/classify/mfoutline.h \
          $$TESSERACT_SRCDIR/src/classify/mfx.h \
          $$TESSERACT_SRCDIR/src/classify/normfeat.h \
          $$TESSERACT_SRCDIR/src/classify/normmatch.h \
          $$TESSERACT_SRCDIR/src/classify/ocrfeatures.h \
          $$TESSERACT_SRCDIR/src/classify/outfeat.h \
          $$TESSERACT_SRCDIR/src/classify/picofeat.h \
          $$TESSERACT_SRCDIR/src/classify/protos.h \
          $$TESSERACT_SRCDIR/src/classify/shapeclassifier.h \
          $$TESSERACT_SRCDIR/src/classify/shapetable.h \
          $$TESSERACT_SRCDIR/src/classify/tessclassifier.h \
          $$TESSERACT_SRCDIR/src/classify/trainingsample.h \
          $$TESSERACT_SRCDIR/src/cutil/bitvec.h \
          $$TESSERACT_SRCDIR/src/cutil/oldlist.h \
          $$TESSERACT_SRCDIR/src/dict/dawg.h \
          $$TESSERACT_SRCDIR/src/dict/dawg_cache.h \
          $$TESSERACT_SRCDIR/src/dict/dict.h \
          $$TESSERACT_SRCDIR/src/dict/matchdefs.h \
          $$TESSERACT_SRCDIR/src/dict/stopper.h \
          $$TESSERACT_SRCDIR/src/dict/trie.h \
          $$TESSERACT_SRCDIR/src/lstm/convolve.h \
          $$TESSERACT_SRCDIR/src/lstm/fullyconnected.h \
          $$TESSERACT_SRCDIR/src/lstm/functions.h \
          $$TESSERACT_SRCDIR/src/lstm/input.h \
          $$TESSERACT_SRCDIR/src/lstm/lstm.h \
          $$TESSERACT_SRCDIR/src/lstm/lstmrecognizer.h \
          $$TESSERACT_SRCDIR/src/lstm/maxpool.h \
          $$TESSERACT_SRCDIR/src/lstm/network.h \
          $$TESSERACT_SRCDIR/src/lstm/networkio.h \
          $$TESSERACT_SRCDIR/src/lstm/networkscratch.h \
          $$TESSERACT_SRCDIR/src/lstm/parallel.h \
          $$TESSERACT_SRCDIR/src/lstm/plumbing.h \
          $$TESSERACT_SRCDIR/src/lstm/recodebeam.h \
          $$TESSERACT_SRCDIR/src/lstm/reconfig.h \
          $$TESSERACT_SRCDIR/src/lstm/reversed.h \
          $$TESSERACT_SRCDIR/src/lstm/series.h \
          $$TESSERACT_SRCDIR/src/lstm/static_shape.h \
          $$TESSERACT_SRCDIR/src/lstm/stridemap.h \
          $$TESSERACT_SRCDIR/src/lstm/tfnetwork.h \
#          $$TESSERACT_SRCDIR/src/lstm/tfnetwork.pb.h \
          $$TESSERACT_SRCDIR/src/lstm/weightmatrix.h \
          $$TESSERACT_SRCDIR/src/opencl/oclkernels.h \
          $$TESSERACT_SRCDIR/src/opencl/openclwrapper.h \
          $$TESSERACT_SRCDIR/src/textord/alignedblob.h \
          $$TESSERACT_SRCDIR/src/textord/baselinedetect.h \
          $$TESSERACT_SRCDIR/src/textord/bbgrid.h \
          $$TESSERACT_SRCDIR/src/textord/blkocc.h \
          $$TESSERACT_SRCDIR/src/textord/blobgrid.h \
          $$TESSERACT_SRCDIR/src/textord/ccnontextdetect.h \
          $$TESSERACT_SRCDIR/src/textord/cjkpitch.h \
          $$TESSERACT_SRCDIR/src/textord/colfind.h \
          $$TESSERACT_SRCDIR/src/textord/colpartition.h \
          $$TESSERACT_SRCDIR/src/textord/colpartitiongrid.h \
          $$TESSERACT_SRCDIR/src/textord/colpartitionset.h \
          $$TESSERACT_SRCDIR/src/textord/devanagari_processing.h \
          $$TESSERACT_SRCDIR/src/textord/drawtord.h \
          $$TESSERACT_SRCDIR/src/textord/edgblob.h \
          $$TESSERACT_SRCDIR/src/textord/edgloop.h \
          $$TESSERACT_SRCDIR/src/textord/equationdetectbase.h \
          $$TESSERACT_SRCDIR/src/textord/fpchop.h \
          $$TESSERACT_SRCDIR/src/textord/gap_map.h \
          $$TESSERACT_SRCDIR/src/textord/imagefind.h \
          $$TESSERACT_SRCDIR/src/textord/linefind.h \
          $$TESSERACT_SRCDIR/src/textord/makerow.h \
          $$TESSERACT_SRCDIR/src/textord/oldbasel.h \
          $$TESSERACT_SRCDIR/src/textord/pithsync.h \
          $$TESSERACT_SRCDIR/src/textord/pitsync1.h \
          $$TESSERACT_SRCDIR/src/textord/scanedg.h \
          $$TESSERACT_SRCDIR/src/textord/sortflts.h \
          $$TESSERACT_SRCDIR/src/textord/strokewidth.h \
          $$TESSERACT_SRCDIR/src/textord/tabfind.h \
          $$TESSERACT_SRCDIR/src/textord/tablefind.h \
          $$TESSERACT_SRCDIR/src/textord/tablerecog.h \
          $$TESSERACT_SRCDIR/src/textord/tabvector.h \
          $$TESSERACT_SRCDIR/src/textord/textlineprojection.h \
          $$TESSERACT_SRCDIR/src/textord/textord.h \
          $$TESSERACT_SRCDIR/src/textord/topitch.h \
          $$TESSERACT_SRCDIR/src/textord/tordmain.h \
          $$TESSERACT_SRCDIR/src/textord/tovars.h \
          $$TESSERACT_SRCDIR/src/textord/underlin.h \
          $$TESSERACT_SRCDIR/src/textord/wordseg.h \
          $$TESSERACT_SRCDIR/src/textord/workingpartset.h \
#          $$TESSERACT_SRCDIR/src/training/degradeimage.h \
#          $$TESSERACT_SRCDIR/src/training/mergenf.h \
          $$TESSERACT_SRCDIR/src/viewer/scrollview.h \
          $$TESSERACT_SRCDIR/src/viewer/svmnode.h \
          $$TESSERACT_SRCDIR/src/viewer/svutil.h \
          $$TESSERACT_SRCDIR/src/wordrec/associate.h \
          $$TESSERACT_SRCDIR/src/wordrec/chop.h \
          $$TESSERACT_SRCDIR/src/wordrec/drawfx.h \
          $$TESSERACT_SRCDIR/src/wordrec/findseam.h \
          $$TESSERACT_SRCDIR/src/wordrec/language_model.h \
          $$TESSERACT_SRCDIR/src/wordrec/lm_consistency.h \
          $$TESSERACT_SRCDIR/src/wordrec/lm_pain_points.h \
          $$TESSERACT_SRCDIR/src/wordrec/lm_state.h \
          $$TESSERACT_SRCDIR/src/wordrec/outlines.h \
          $$TESSERACT_SRCDIR/src/wordrec/params_model.h \
          $$TESSERACT_SRCDIR/src/wordrec/plotedges.h \
          $$TESSERACT_SRCDIR/src/wordrec/render.h \
          $$TESSERACT_SRCDIR/src/wordrec/wordrec.h \
#          $$TESSERACT_SRCDIR/src/training/common/commandlineflags.h \
#          $$TESSERACT_SRCDIR/src/training/common/commontraining.h \
#          $$TESSERACT_SRCDIR/src/training/common/ctc.h \
#          $$TESSERACT_SRCDIR/src/training/common/errorcounter.h \
#          $$TESSERACT_SRCDIR/src/training/common/export.h \
#          $$TESSERACT_SRCDIR/src/training/common/intfeaturedist.h \
#          $$TESSERACT_SRCDIR/src/training/common/intfeaturemap.h \
#          $$TESSERACT_SRCDIR/src/training/common/mastertrainer.h \
#          $$TESSERACT_SRCDIR/src/training/common/networkbuilder.h \
#          $$TESSERACT_SRCDIR/src/training/common/sampleiterator.h \
#          $$TESSERACT_SRCDIR/src/training/common/trainingsampleset.h \
#          $$TESSERACT_SRCDIR/src/training/pango/boxchar.h \
#          $$TESSERACT_SRCDIR/src/training/pango/export.h \
#          $$TESSERACT_SRCDIR/src/training/pango/ligature_table.h \
#          $$TESSERACT_SRCDIR/src/training/pango/pango_font_info.h \
#          $$TESSERACT_SRCDIR/src/training/pango/stringrenderer.h \
#          $$TESSERACT_SRCDIR/src/training/pango/tlog.h \
#          $$TESSERACT_SRCDIR/src/training/unicharset/export.h \
#          $$TESSERACT_SRCDIR/src/training/unicharset/fileio.h \
#          $$TESSERACT_SRCDIR/src/training/unicharset/icuerrorcode.h \
#          $$TESSERACT_SRCDIR/src/training/unicharset/lang_model_helpers.h \
#          $$TESSERACT_SRCDIR/src/training/unicharset/lstmtester.h \
#          $$TESSERACT_SRCDIR/src/training/unicharset/lstmtrainer.h \
#          $$TESSERACT_SRCDIR/src/training/unicharset/normstrngs.h \
#          $$TESSERACT_SRCDIR/src/training/unicharset/unicharset_training_utils.h \
#          $$TESSERACT_SRCDIR/src/training/unicharset/validate_grapheme.h \
#          $$TESSERACT_SRCDIR/src/training/unicharset/validate_indic.h \
#          $$TESSERACT_SRCDIR/src/training/unicharset/validate_javanese.h \
#          $$TESSERACT_SRCDIR/src/training/unicharset/validate_khmer.h \
#          $$TESSERACT_SRCDIR/src/training/unicharset/validate_myanmar.h \
#          $$TESSERACT_SRCDIR/src/training/unicharset/validator.h

SOURCES += $$TESSERACT_SRCDIR/src/api/altorenderer.cpp \
          $$TESSERACT_SRCDIR/src/api/baseapi.cpp \
          $$TESSERACT_SRCDIR/src/api/capi.cpp \
          $$TESSERACT_SRCDIR/src/api/hocrrenderer.cpp \
          $$TESSERACT_SRCDIR/src/api/lstmboxrenderer.cpp \
          $$TESSERACT_SRCDIR/src/api/pdfrenderer.cpp \
          $$TESSERACT_SRCDIR/src/api/renderer.cpp \
#          $$TESSERACT_SRCDIR/src/api/tesseractmain.cpp \
          $$TESSERACT_SRCDIR/src/api/wordstrboxrenderer.cpp \
          $$TESSERACT_SRCDIR/src/arch/dotproduct.cpp \
#          $$TESSERACT_SRCDIR/src/arch/dotproductavx.cpp \
#          $$TESSERACT_SRCDIR/src/arch/dotproductfma.cpp \
#          $$TESSERACT_SRCDIR/src/arch/dotproductsse.cpp \
          $$TESSERACT_SRCDIR/src/arch/intsimdmatrix.cpp \
#          $$TESSERACT_SRCDIR/src/arch/intsimdmatrixavx2.cpp \
#          $$TESSERACT_SRCDIR/src/arch/intsimdmatrixneon.cpp \
#          $$TESSERACT_SRCDIR/src/arch/intsimdmatrixsse.cpp \
          $$TESSERACT_SRCDIR/src/arch/simddetect.cpp \
          $$TESSERACT_SRCDIR/src/ccmain/adaptions.cpp \
          $$TESSERACT_SRCDIR/src/ccmain/applybox.cpp \
          $$TESSERACT_SRCDIR/src/ccmain/control.cpp \
          $$TESSERACT_SRCDIR/src/ccmain/docqual.cpp \
          $$TESSERACT_SRCDIR/src/ccmain/equationdetect.cpp \
          $$TESSERACT_SRCDIR/src/ccmain/fixspace.cpp \
          $$TESSERACT_SRCDIR/src/ccmain/fixxht.cpp \
          $$TESSERACT_SRCDIR/src/ccmain/linerec.cpp \
          $$TESSERACT_SRCDIR/src/ccmain/ltrresultiterator.cpp \
          $$TESSERACT_SRCDIR/src/ccmain/mutableiterator.cpp \
          $$TESSERACT_SRCDIR/src/ccmain/osdetect.cpp \
          $$TESSERACT_SRCDIR/src/ccmain/output.cpp \
          $$TESSERACT_SRCDIR/src/ccmain/pageiterator.cpp \
          $$TESSERACT_SRCDIR/src/ccmain/pagesegmain.cpp \
          $$TESSERACT_SRCDIR/src/ccmain/pagewalk.cpp \
          $$TESSERACT_SRCDIR/src/ccmain/par_control.cpp \
          $$TESSERACT_SRCDIR/src/ccmain/paragraphs.cpp \
          $$TESSERACT_SRCDIR/src/ccmain/paramsd.cpp \
          $$TESSERACT_SRCDIR/src/ccmain/pgedit.cpp \
          $$TESSERACT_SRCDIR/src/ccmain/recogtraining.cpp \
          $$TESSERACT_SRCDIR/src/ccmain/reject.cpp \
          $$TESSERACT_SRCDIR/src/ccmain/resultiterator.cpp \
          $$TESSERACT_SRCDIR/src/ccmain/superscript.cpp \
          $$TESSERACT_SRCDIR/src/ccmain/tessbox.cpp \
          $$TESSERACT_SRCDIR/src/ccmain/tessedit.cpp \
          $$TESSERACT_SRCDIR/src/ccmain/tesseractclass.cpp \
          $$TESSERACT_SRCDIR/src/ccmain/tessvars.cpp \
          $$TESSERACT_SRCDIR/src/ccmain/tfacepp.cpp \
          $$TESSERACT_SRCDIR/src/ccmain/thresholder.cpp \
          $$TESSERACT_SRCDIR/src/ccmain/werdit.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/blamer.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/blobbox.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/blobs.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/blread.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/boxread.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/boxword.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/ccstruct.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/coutln.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/detlinefit.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/dppoint.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/fontinfo.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/image.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/imagedata.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/linlsq.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/matrix.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/mod128.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/normalis.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/ocrblock.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/ocrpara.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/ocrrow.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/otsuthr.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/pageres.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/params_training_featdef.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/pdblock.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/points.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/polyaprx.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/polyblk.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/quadlsq.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/quspline.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/ratngs.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/rect.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/rejctmap.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/seam.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/split.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/statistc.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/stepblob.cpp \
          $$TESSERACT_SRCDIR/src/ccstruct/werd.cpp \
          $$TESSERACT_SRCDIR/src/ccutil/ambigs.cpp \
          $$TESSERACT_SRCDIR/src/ccutil/bitvector.cpp \
          $$TESSERACT_SRCDIR/src/ccutil/ccutil.cpp \
          $$TESSERACT_SRCDIR/src/ccutil/clst.cpp \
          $$TESSERACT_SRCDIR/src/ccutil/elst.cpp \
          $$TESSERACT_SRCDIR/src/ccutil/elst2.cpp \
          $$TESSERACT_SRCDIR/src/ccutil/errcode.cpp \
          $$TESSERACT_SRCDIR/src/ccutil/indexmapbidi.cpp \
          $$TESSERACT_SRCDIR/src/ccutil/mainblk.cpp \
          $$TESSERACT_SRCDIR/src/ccutil/params.cpp \
          $$TESSERACT_SRCDIR/src/ccutil/scanutils.cpp \
          $$TESSERACT_SRCDIR/src/ccutil/serialis.cpp \
          $$TESSERACT_SRCDIR/src/ccutil/tessdatamanager.cpp \
          $$TESSERACT_SRCDIR/src/ccutil/tprintf.cpp \
          $$TESSERACT_SRCDIR/src/ccutil/unichar.cpp \
          $$TESSERACT_SRCDIR/src/ccutil/unicharcompress.cpp \
          $$TESSERACT_SRCDIR/src/ccutil/unicharmap.cpp \
          $$TESSERACT_SRCDIR/src/ccutil/unicharset.cpp \
          $$TESSERACT_SRCDIR/src/ccutil/universalambigs.cpp \
          $$TESSERACT_SRCDIR/src/classify/adaptive.cpp \
          $$TESSERACT_SRCDIR/src/classify/adaptmatch.cpp \
          $$TESSERACT_SRCDIR/src/classify/blobclass.cpp \
          $$TESSERACT_SRCDIR/src/classify/classify.cpp \
          $$TESSERACT_SRCDIR/src/classify/cluster.cpp \
          $$TESSERACT_SRCDIR/src/classify/clusttool.cpp \
          $$TESSERACT_SRCDIR/src/classify/cutoffs.cpp \
          $$TESSERACT_SRCDIR/src/classify/featdefs.cpp \
          $$TESSERACT_SRCDIR/src/classify/float2int.cpp \
          $$TESSERACT_SRCDIR/src/classify/fpoint.cpp \
          $$TESSERACT_SRCDIR/src/classify/intfeaturespace.cpp \
          $$TESSERACT_SRCDIR/src/classify/intfx.cpp \
          $$TESSERACT_SRCDIR/src/classify/intmatcher.cpp \
          $$TESSERACT_SRCDIR/src/classify/intproto.cpp \
          $$TESSERACT_SRCDIR/src/classify/kdtree.cpp \
          $$TESSERACT_SRCDIR/src/classify/mf.cpp \
          $$TESSERACT_SRCDIR/src/classify/mfoutline.cpp \
          $$TESSERACT_SRCDIR/src/classify/mfx.cpp \
          $$TESSERACT_SRCDIR/src/classify/normfeat.cpp \
          $$TESSERACT_SRCDIR/src/classify/normmatch.cpp \
          $$TESSERACT_SRCDIR/src/classify/ocrfeatures.cpp \
          $$TESSERACT_SRCDIR/src/classify/outfeat.cpp \
          $$TESSERACT_SRCDIR/src/classify/picofeat.cpp \
          $$TESSERACT_SRCDIR/src/classify/protos.cpp \
          $$TESSERACT_SRCDIR/src/classify/shapeclassifier.cpp \
          $$TESSERACT_SRCDIR/src/classify/shapetable.cpp \
          $$TESSERACT_SRCDIR/src/classify/tessclassifier.cpp \
          $$TESSERACT_SRCDIR/src/classify/trainingsample.cpp \
          $$TESSERACT_SRCDIR/src/cutil/oldlist.cpp \
          $$TESSERACT_SRCDIR/src/dict/context.cpp \
          $$TESSERACT_SRCDIR/src/dict/dawg.cpp \
          $$TESSERACT_SRCDIR/src/dict/dawg_cache.cpp \
          $$TESSERACT_SRCDIR/src/dict/dict.cpp \
          $$TESSERACT_SRCDIR/src/dict/hyphen.cpp \
          $$TESSERACT_SRCDIR/src/dict/permdawg.cpp \
          $$TESSERACT_SRCDIR/src/dict/stopper.cpp \
          $$TESSERACT_SRCDIR/src/dict/trie.cpp \
          $$TESSERACT_SRCDIR/src/lstm/convolve.cpp \
          $$TESSERACT_SRCDIR/src/lstm/fullyconnected.cpp \
          $$TESSERACT_SRCDIR/src/lstm/functions.cpp \
          $$TESSERACT_SRCDIR/src/lstm/input.cpp \
          $$TESSERACT_SRCDIR/src/lstm/lstm.cpp \
          $$TESSERACT_SRCDIR/src/lstm/lstmrecognizer.cpp \
          $$TESSERACT_SRCDIR/src/lstm/maxpool.cpp \
          $$TESSERACT_SRCDIR/src/lstm/network.cpp \
          $$TESSERACT_SRCDIR/src/lstm/networkio.cpp \
          $$TESSERACT_SRCDIR/src/lstm/parallel.cpp \
          $$TESSERACT_SRCDIR/src/lstm/plumbing.cpp \
          $$TESSERACT_SRCDIR/src/lstm/recodebeam.cpp \
          $$TESSERACT_SRCDIR/src/lstm/reconfig.cpp \
          $$TESSERACT_SRCDIR/src/lstm/reversed.cpp \
          $$TESSERACT_SRCDIR/src/lstm/series.cpp \
          $$TESSERACT_SRCDIR/src/lstm/stridemap.cpp \
          $$TESSERACT_SRCDIR/src/lstm/tfnetwork.cpp \
#          $$TESSERACT_SRCDIR/src/lstm/tfnetwork.pb.cc \
          $$TESSERACT_SRCDIR/src/lstm/weightmatrix.cpp \
          $$TESSERACT_SRCDIR/src/opencl/openclwrapper.cpp \
          $$TESSERACT_SRCDIR/src/textord/alignedblob.cpp \
          $$TESSERACT_SRCDIR/src/textord/baselinedetect.cpp \
          $$TESSERACT_SRCDIR/src/textord/bbgrid.cpp \
          $$TESSERACT_SRCDIR/src/textord/blkocc.cpp \
          $$TESSERACT_SRCDIR/src/textord/blobgrid.cpp \
          $$TESSERACT_SRCDIR/src/textord/ccnontextdetect.cpp \
          $$TESSERACT_SRCDIR/src/textord/cjkpitch.cpp \
          $$TESSERACT_SRCDIR/src/textord/colfind.cpp \
          $$TESSERACT_SRCDIR/src/textord/colpartition.cpp \
          $$TESSERACT_SRCDIR/src/textord/colpartitiongrid.cpp \
          $$TESSERACT_SRCDIR/src/textord/colpartitionset.cpp \
          $$TESSERACT_SRCDIR/src/textord/devanagari_processing.cpp \
          $$TESSERACT_SRCDIR/src/textord/drawtord.cpp \
          $$TESSERACT_SRCDIR/src/textord/edgblob.cpp \
          $$TESSERACT_SRCDIR/src/textord/edgloop.cpp \
          $$TESSERACT_SRCDIR/src/textord/equationdetectbase.cpp \
          $$TESSERACT_SRCDIR/src/textord/fpchop.cpp \
          $$TESSERACT_SRCDIR/src/textord/gap_map.cpp \
          $$TESSERACT_SRCDIR/src/textord/imagefind.cpp \
          $$TESSERACT_SRCDIR/src/textord/linefind.cpp \
          $$TESSERACT_SRCDIR/src/textord/makerow.cpp \
          $$TESSERACT_SRCDIR/src/textord/oldbasel.cpp \
          $$TESSERACT_SRCDIR/src/textord/pithsync.cpp \
          $$TESSERACT_SRCDIR/src/textord/pitsync1.cpp \
          $$TESSERACT_SRCDIR/src/textord/scanedg.cpp \
          $$TESSERACT_SRCDIR/src/textord/sortflts.cpp \
          $$TESSERACT_SRCDIR/src/textord/strokewidth.cpp \
          $$TESSERACT_SRCDIR/src/textord/tabfind.cpp \
          $$TESSERACT_SRCDIR/src/textord/tablefind.cpp \
          $$TESSERACT_SRCDIR/src/textord/tablerecog.cpp \
          $$TESSERACT_SRCDIR/src/textord/tabvector.cpp \
          $$TESSERACT_SRCDIR/src/textord/textlineprojection.cpp \
          $$TESSERACT_SRCDIR/src/textord/textord.cpp \
          $$TESSERACT_SRCDIR/src/textord/topitch.cpp \
          $$TESSERACT_SRCDIR/src/textord/tordmain.cpp \
          $$TESSERACT_SRCDIR/src/textord/tospace.cpp \
          $$TESSERACT_SRCDIR/src/textord/tovars.cpp \
          $$TESSERACT_SRCDIR/src/textord/underlin.cpp \
          $$TESSERACT_SRCDIR/src/textord/wordseg.cpp \
          $$TESSERACT_SRCDIR/src/textord/workingpartset.cpp \
#          $$TESSERACT_SRCDIR/src/training/ambiguous_words.cpp \
#          $$TESSERACT_SRCDIR/src/training/classifier_tester.cpp \
#          $$TESSERACT_SRCDIR/src/training/cntraining.cpp \
#          $$TESSERACT_SRCDIR/src/training/combine_lang_model.cpp \
#          $$TESSERACT_SRCDIR/src/training/combine_tessdata.cpp \
#          $$TESSERACT_SRCDIR/src/training/dawg2wordlist.cpp \
#          $$TESSERACT_SRCDIR/src/training/degradeimage.cpp \
#          $$TESSERACT_SRCDIR/src/training/lstmeval.cpp \
#          $$TESSERACT_SRCDIR/src/training/lstmtraining.cpp \
#          $$TESSERACT_SRCDIR/src/training/merge_unicharsets.cpp \
#          $$TESSERACT_SRCDIR/src/training/mergenf.cpp \
#          $$TESSERACT_SRCDIR/src/training/mftraining.cpp \
#          $$TESSERACT_SRCDIR/src/training/set_unicharset_properties.cpp \
#          $$TESSERACT_SRCDIR/src/training/shapeclustering.cpp \
#          $$TESSERACT_SRCDIR/src/training/text2image.cpp \
#          $$TESSERACT_SRCDIR/src/training/unicharset_extractor.cpp \
#          $$TESSERACT_SRCDIR/src/training/wordlist2dawg.cpp \
          $$TESSERACT_SRCDIR/src/viewer/scrollview.cpp \
          $$TESSERACT_SRCDIR/src/viewer/svmnode.cpp \
#          $$TESSERACT_SRCDIR/src/viewer/svpaint.cpp \
          $$TESSERACT_SRCDIR/src/viewer/svutil.cpp \
          $$TESSERACT_SRCDIR/src/wordrec/associate.cpp \
          $$TESSERACT_SRCDIR/src/wordrec/chop.cpp \
          $$TESSERACT_SRCDIR/src/wordrec/chopper.cpp \
          $$TESSERACT_SRCDIR/src/wordrec/drawfx.cpp \
          $$TESSERACT_SRCDIR/src/wordrec/findseam.cpp \
          $$TESSERACT_SRCDIR/src/wordrec/gradechop.cpp \
          $$TESSERACT_SRCDIR/src/wordrec/language_model.cpp \
          $$TESSERACT_SRCDIR/src/wordrec/lm_consistency.cpp \
          $$TESSERACT_SRCDIR/src/wordrec/lm_pain_points.cpp \
          $$TESSERACT_SRCDIR/src/wordrec/lm_state.cpp \
          $$TESSERACT_SRCDIR/src/wordrec/outlines.cpp \
          $$TESSERACT_SRCDIR/src/wordrec/params_model.cpp \
          $$TESSERACT_SRCDIR/src/wordrec/pieces.cpp \
          $$TESSERACT_SRCDIR/src/wordrec/plotedges.cpp \
          $$TESSERACT_SRCDIR/src/wordrec/render.cpp \
          $$TESSERACT_SRCDIR/src/wordrec/segsearch.cpp \
          $$TESSERACT_SRCDIR/src/wordrec/tface.cpp \
          $$TESSERACT_SRCDIR/src/wordrec/wordclass.cpp \
          $$TESSERACT_SRCDIR/src/wordrec/wordrec.cpp \
#          $$TESSERACT_SRCDIR/src/training/common/commandlineflags.cpp \
#          $$TESSERACT_SRCDIR/src/training/common/commontraining.cpp \
#          $$TESSERACT_SRCDIR/src/training/common/ctc.cpp \
#          $$TESSERACT_SRCDIR/src/training/common/errorcounter.cpp \
#          $$TESSERACT_SRCDIR/src/training/common/intfeaturedist.cpp \
#          $$TESSERACT_SRCDIR/src/training/common/intfeaturemap.cpp \
#          $$TESSERACT_SRCDIR/src/training/common/mastertrainer.cpp \
#          $$TESSERACT_SRCDIR/src/training/common/networkbuilder.cpp \
#          $$TESSERACT_SRCDIR/src/training/common/sampleiterator.cpp \
#          $$TESSERACT_SRCDIR/src/training/common/trainingsampleset.cpp \
#          $$TESSERACT_SRCDIR/src/training/pango/boxchar.cpp \
#          $$TESSERACT_SRCDIR/src/training/pango/ligature_table.cpp \
#          $$TESSERACT_SRCDIR/src/training/pango/pango_font_info.cpp \
#          $$TESSERACT_SRCDIR/src/training/pango/stringrenderer.cpp \
#          $$TESSERACT_SRCDIR/src/training/pango/tlog.cpp \
#          $$TESSERACT_SRCDIR/src/training/unicharset/fileio.cpp \
#          $$TESSERACT_SRCDIR/src/training/unicharset/icuerrorcode.cpp \
#          $$TESSERACT_SRCDIR/src/training/unicharset/lang_model_helpers.cpp \
#          $$TESSERACT_SRCDIR/src/training/unicharset/lstmtester.cpp \
#          $$TESSERACT_SRCDIR/src/training/unicharset/lstmtrainer.cpp \
#          $$TESSERACT_SRCDIR/src/training/unicharset/normstrngs.cpp \
#          $$TESSERACT_SRCDIR/src/training/unicharset/unicharset_training_utils.cpp \
#          $$TESSERACT_SRCDIR/src/training/unicharset/validate_grapheme.cpp \
#          $$TESSERACT_SRCDIR/src/training/unicharset/validate_indic.cpp \
#          $$TESSERACT_SRCDIR/src/training/unicharset/validate_javanese.cpp \
#          $$TESSERACT_SRCDIR/src/training/unicharset/validate_khmer.cpp \
#          $$TESSERACT_SRCDIR/src/training/unicharset/validate_myanmar.cpp \
#          $$TESSERACT_SRCDIR/src/training/unicharset/validator.cpp

message("-----------------end------------- ")

