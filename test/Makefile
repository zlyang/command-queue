EXECUTABLE = cqueue_test
CXX = g++
SOURCES = \
	cqueue_test.cpp

OBJS = $(patsubst %.cpp,%.o,$(SOURCES))

CPPFLAGS = \
	-std=c++11 \
	-I.. \

LIBADD = \
	-lpthread \

.PHONY:all
all: $(EXECUTABLE)

ifneq ($(MAKECMDGOALS),clean)
include $(OBJS:.o=.d)
endif

$(EXECUTABLE): $(OBJS)
	$(CXX) -o $(EXECUTABLE) $(OBJS) $(LIBADD)

%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) -o $@ -c $< $(CPPFLAGS)

%.d: %.cpp
	set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

.PHONY:clean
clean:
	rm -f *.d *.o *.d.* $(EXECUTABLE)
