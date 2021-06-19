FROM ubuntu
# fetch submodules
RUN git submodule update --init lib/ tools/ extmod/
    && git submodule update --init --recursive ports/esp32s2/
# install deps
RUN pip install -r requirements-dev.txt
    && sudo apt-get install -y gettext ninja-build
# setup idf tools
RUN source ports/esp32s2/esp-idf/export.sh
    && $IDF_PATH/tools/idf_tools.py --non-interactive install cmake
    && $IDF_PATH/tools/idf_tools.py --non-interactive install required
    && $IDF_PATH/tools/idf_tools.py --non-interactive install-python-env
    && rm -rf .idf_tools/dist
# build mpy-cross
RUN make -jC mpy-cross
