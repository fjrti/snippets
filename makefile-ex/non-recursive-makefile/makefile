TARGET := xxxx
CC := gcc
AR := ar
OBJ_DIR := objs
OBJS := $(OBJ_DIR)/xxxx.o
#objs in current directory
COMPILE  =  $(CC) $(CFLAGS_GLOBAL) $(CFLAGS_LOCAL) -MD -c -o $@ $<
MAKELIB  = $(AR) -cr $@ $^
CFLAGS_LOCAL =
#the directory where the objs put
all: $(TARGET)
$(OBJ_DIR):
	mkdir $(OBJ_DIR)
$(OBJ_DIR)/%.o : %.c
	$(COMPILE)
-include $(OBJS:.o=.d)
#dir := tt
#-include $(dir)/tt.mk
#dir := xxxxx
#-include $(dir)
$(TARGET): $(OBJ_DIR) $(OBJS) $(LIBS_LIST)
	$(CC) $(OBJS) $(LDFLAGS_PATH) $(LIBS_LIST) $(LDFLAGS_GLOBAL) -o $@
clean:
	rm -rf $(OBJ_DIR) $(CLEAN_LIST) $(TARGET)
