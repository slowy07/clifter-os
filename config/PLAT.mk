#Platform
PLAT?=pc

ifeq ($(PLAT),$(filter $(PLAT),pc))
 $(info PC Platform)
  PLAT_S:="pc"
else
 $(error SUPPORTED Platforms are {pc} . Change via ./configure --plat=PLAT_NAME) 
endif
export PLAT
export PLAT_S