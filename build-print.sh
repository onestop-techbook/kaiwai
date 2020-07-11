#!/bin/sh
echo [100book]
echo Building 100book.pdf into src directory...
docker run --rm -v $PWD/src:/work vvakame/review:3.1 /bin/sh -c "cd /work && review-pdfmaker config-print.yml"
