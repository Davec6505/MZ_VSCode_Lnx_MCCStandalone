DEVICE := 32MZ1024EFH064





PATH_TO_IDE_BIN=/opt/microchip/mplabx/v6.20/mplab_platform/platform/../mplab_ide/modules/../../bin/
# Adding MPLAB X bin directory to path.
PATH:=/opt/microchip/mplabx/v6.20/mplab_platform/platform/../mplab_ide/modules/../../bin/:$(PATH)

OS_CURRENT="$(shell uname -s)"
MP_CC="/opt/microchip/xc32/v4.45/bin/xc32-gcc"
MP_CPPC="/opt/microchip/xc32/v4.45/bin/xc32-g++"
# MP_BC is not defined
MP_AS="/opt/microchip/xc32/v4.45/bin/xc32-as"
MP_LD="/opt/microchip/xc32/v4.45/bin/xc32-ld"
MP_AR="/opt/microchip/xc32/v4.45/bin/xc32-ar"
MP_CC_DIR="/opt/microchip/xc32/v4.45/bin"
MP_CPPC_DIR="/opt/microchip/xc32/v4.45/bin"
# MP_BC_DIR is not defined
MP_AS_DIR="/opt/microchip/xc32/v4.45/bin"
MP_LD_DIR="/opt/microchip/xc32/v4.45/bin"
MP_AR_DIR="/opt/microchip/xc32/v4.45/bin"
DFP_DIR=/opt/microchip/mplabx/v6.20/packs/Microchip/PIC32MZ-EF_DFP/1.4.168
# Generate hex file
MP_BIN2HEX :="/opt/microchip/xc32/v4.45/bin"/xc32-bin2hex


# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 


IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/FC_Blink.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
#OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
#DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

MODULE := main
ROOT      := .
OBJ_DIR   := $(ROOT)/objs
SRC_DIR   := src
MCC_DIR	  := $(SRC_DIR)/config
CON_DIR   := $(MCC_DIR)/default
PIR_DIR   := $(CON_DIR)/peripheral
IO_DIR	  := $(CON_DIR)/stdio
BIN_DIR   := $(ROOT)/bins
OUT_DIR   := $(ROOT)/other
INC_DIR   := 
TARGET    := $(BIN_DIR)/$(MODULE)
DIR  	  := $(PIR_DIR)/evic  \
	     	 $(PIR_DIR)/clk \
	     	 $(PIR_DIR)/gpio \
			 $(PIR_DIR)/coretimer \
			 $(IO_DIR)  \
			 $(MCC_DIR) \
			 $(CON_DIR) \
			 $(SRC_DIR)

INC := -I$(SRC_DIR)/ -I$(CON_DIR)
	     

COMPILER  := c
#COMPILER  := c++
ifeq ($(COMPILER),c)
CC := $(MP_CC)
AS := $(MP_AS)
MCU := -mprocessor=$(DEVICE)
STD := c99
else
CC := $(MP_CPPC)
MCU := -mprocessor=$(DEVICE)
STD := c90
endif


#Direct the compiler outputs for pcode
DIRECT_LINK :=  -nostartfiles -o $(BIN_DIR)/$(MODULE).elf -DXPRJ_default=default  -Wl,--defsym=__MPLAB_BUILD=1,--script="$(CON_DIR)/p$(DEVICE).ld",--defsym=_min_heap_size=512,-gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map=$(OUT_DIR)/$(MODULE).map,--memorysummary,$(OUT_DIR)/memoryfile.xml -mdfp=$(DFP_DIR) 
       

#"/opt/microchip/xc32/v4.45/bin"/xc32-bin2hex dist/default/production/FC_Blink.X.production.elf 


# Direct compiler output for linker 
DIRECT_OBJ :=  -g -x c -c  \
				-ffunction-sections -fdata-sections -O1 -fno-common \
				$(INC) -Werror -Wall -MP -MMD -MF -o \
				-DXPRJ_default=default -mdfp=$(DFP_DIR)
# -save-temps=obj


DIRECT_ASM :=   -c  -DXPRJ_default=default    -Wa,--defsym=__MPLAB_BUILD=1,-MD=$(OBJ_DIR)/$(SRC_DIR)/startup.o.asm.d,--gdwarf-2 -mdfp=$(DFP_DIR) -MMD -MF $(OBJ_DIR)/startup.o.d 
#"build/default/production/startup.o.d"
#-MD="build/default/production/startup.o.asm.d"
#-o $(OBJ_DIR)/$(SRC_DIR)/startup.o 


#SRC := $(foreach dir,$(DIR),$(filter %.c %.s,$(dir)))
SRCS  := $(foreach dir,$(DIR),$(wildcard $(dir)/*.c))
#SRC += main.c

ASM  := $(foreach dir,$(DIR),$(wildcard $(dir)/*.S))
ASMS  := $(ASM:%.S=$(OBJ_DIR)/%.o)

OBJ  := $(SRCS:%.c=%.o)
OBJS  := $(SRCS:%.c=$(OBJ_DIR)/%.o)
OBJS += $(ASMS)

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo $(OBJS)
	$(CC) $(MCU) $(DIRECT_LINK) -o $@ $^ 
	$(MP_BIN2HEX) $@
#$(call move)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(MCU) $(DIRECT_OBJ) -c $< -o $@ $(INC)

$(OBJ_DIR)/%.o: %.S
	$(CC) $(MCU) $(DIRECT_ASM) -o $@ $<




build_dir:
	mkdir -p $(OBJ_DIR)/$(PIR_DIR)/evic
	mkdir -p $(OBJ_DIR)/$(PIR_DIR)/gpio
	mkdir -p $(OBJ_DIR)/$(PIR_DIR)/clk
	mkdir -p $(OBJ_DIR)/$(PIR_DIR)/coretimer
	mkdir -p $(OBJ_DIR)/$(IO_DIR)
	mkdir -p $(OBJ_DIR)/$(MCC_DIR)




define move
	rm -r $(BIN_DIR)/*.d $(BIN_DIR)/*.o $(BIN_DIR)/*.o $(BIN_DIR)/*.sdb $(BIN_DIR)/*.rlf \
	      $(BIN_DIR)/*.sym $(BIN_DIR)/*.cmf $(BIN_DIR)/*.i
	mv $(BIN_DIR)/*.hxl $(BIN_DIR)/*.lst $(OUT_DIR)
endef

clean:
	rm -rf $(BIN_DIR)/* \
	       $(OBJ_DIR)/*.o  $(OBJ_DIR)/*.i $(OBJ_DIR)/*.d \
	       $(OBJ_DIR)/$(PIR_DIR)/evic/*.O  \
	       $(OBJ_DIR)/$(PIR_DIR)/gpio/*.O \
	       $(OBJ_DIR)/$(PIR_DIR)/clk/*.O  \
		   $(OBJ_DIR)/$(IO_DIR)/*.O  \
		   $(OBJ_DIR)/$(MCC_DIR)/*.O \
		   $(OBJ_DIR)/$(SRC_DIR)/*.o \
		   $(OUT_DIR)/*.map \
		   $(OUT_DIR)/*.xml


.PHONY: clean  build_dir


