objects= get_ifi_info.o parse_hostnetworkmask.o wrapunix.o get_printMAC.o getMAC_from_arp.o
compiled-objects=error.o wrapsock.o
CFLAG=-g
ifdef DEBUG
  CFLAG+= -DDEBUG
endif
CC=gcc

.PHONY :clean all request response request-clean response-clean
all:request response
request:arprequest
response:arpresponse

arprequest :$(objects) arprequest.c arpdeceive.h
	gcc	$(CFLAG) arprequest.c $(objects) $(compiled-objects)	-o	arprequest
	cp	arprequest	/bin/
	
arpresponse:$(objects) arpresponse.c arpdeceive.h
	gcc	$(CFLAG) arpresponse.c $(objects) $(compiled-objects)	-o	arpresponse
	cp	arpresponse	/bin/
	
$(objects) : %.o : %.c selfdefine.h
	$(CC)	-c	$(CFLAG)	$<	-o	$@ 
	
#清除中间生成的所有目标文件	
clean:request-clean response-clean
request-clean:
	rm	-f arprequest /bin/arprequest	$(objects)
response-clean:
	rm	-f arpresponse /bin/arpresponse	$(objects)

