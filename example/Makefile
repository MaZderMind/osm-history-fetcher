#------------------------------------------------------------------------------
#
#  osm history fetcher makefile
#
#------------------------------------------------------------------------------

#CXX = g++
CXX = clang++

CXXFLAGS = -g -O3 -Wall -Wextra -pedantic
CXXFLAGS += `getconf LFS_CFLAGS`
#CXXFLAGS += -Wredundant-decls -Wdisabled-optimization
#CXXFLAGS += -Wpadded -Winline

# path to includes
CXXFLAGS += -I/usr/include/libxml2/

# path to includes
CXXFLAGS += -I../include/

# compile & link against expat to have xml reading support
LDFLAGS += -lexpat

.PHONY: all clean install

all: osm-history-fetcher

osm-history-fetcher: fetcher.cpp ../include/fetcher.hpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

install:
	install -m 755 -g root -o root -d $(DESTDIR)/usr/bin
	install -m 755 -g root -o root osm-history-fetcher $(DESTDIR)/usr/bin/osm-history-fetcher

clean:
	rm -f *.o core osm-history-fetcher

check:
	cppcheck --enable=all *.cpp

# This will try to compile each include file on its own to detect missing
# #include directives. Note that if this reports [OK], it is not enough
# to be sure it will compile in production code. But if it reports [FAILED]
# we know we are missing something.
check-includes:
	echo "check includes report:" >check-includes-report; \
	for FILE in *.hpp *.cpp; do \
		echo "$${FILE}:" >>check-includes-report; \
		echo -n "$${FILE} "; \
		if `g++ -I include $${FILE} 2>>check-includes-report`; then \
			echo "[OK]"; \
		else \
			echo "[FAILED]"; \
		fi; \
		rm -f $${FILE}.gch; \
	done

indent:
	astyle --style=java --indent-namespaces --indent-switches --pad-header --suffix=none --recursive include/\*.hpp examples/\*.cpp examples/\*.hpp osmjs/\*.cpp test/\*.cpp

#deb:
#	debuild -I -us -uc

#deb-clean:
#	debuild clean
