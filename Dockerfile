FROM ubuntu
ARG DEBIAN_FRONTEND=noninteractive
# install deps
RUN apt-get update && apt-get install -y python3 python3-pip gettext ninja-build &&\
    pip3 install -r requirements-dev.txt
# setup idf tools
RUN source ports/esp32s2/esp-idf/export.sh &&\
    $IDF_PATH/tools/idf_tools.py --non-interactive install cmake &&\
    $IDF_PATH/tools/idf_tools.py --non-interactive install required &&\
    $IDF_PATH/tools/idf_tools.py --non-interactive install-python-env &&\
    rm -rf .idf_tools/dist
# build mpy-cross
RUN make -jC mpy-cross
