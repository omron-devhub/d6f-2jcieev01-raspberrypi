
.PHONY: d6f-ph0025 d6f-ph0505 d6f-ph0550 d6f-10 d6f-20 d6f-50 d6f-70

cpplint_flags:=--filter=-readability/casting,-build/include_subdir
ifeq (x$(cpplint),x)
cpplint := @echo lint with cpplint, option:
endif
ifeq (x$(cppcheck),x)
cppcheck := @echo lint with cppcheck, option:
endif

all: d6f-ph0025 d6f-ph0505 d6f-ph5050 d6f-10 d6f-20 d6f-50 d6f-70
# all: d6f-ph0505

d6f-ph0025: d6f-ph0025.c
	$(cpplint) $(cpplint_flags) $^
	$(cppcheck) --enable=all $^
	gcc $(CFLAGS) $^ -o $@

d6f-ph0505: d6f-ph0505.c
	$(cpplint) $(cpplint_flags) $^
	$(cppcheck) --enable=all $^
	gcc $(CFLAGS) $^ -o $@

d6f-ph0550: d6f-ph5050.c
	$(cpplint) $(cpplint_flags) $^
	$(cppcheck) --enable=all $^
	gcc $(CFLAGS) $^ -o $@

d6f-10: d6f-10.c
	$(cpplint) $(cpplint_flags) $^
	$(cppcheck) --enable=all $^
	gcc $(CFLAGS) $^ -o $@

d6f-20: d6f-20.c
	$(cpplint) $(cpplint_flags) $^
	$(cppcheck) --enable=all $^
	gcc $(CFLAGS) $^ -o $@

d6f-50: d6f-50.c
	$(cpplint) $(cpplint_flags) $^
	$(cppcheck) --enable=all $^
	gcc $(CFLAGS) $^ -o $@

d6f-70: d6f-70.c
	$(cpplint) $(cpplint_flags) $^
	$(cppcheck) --enable=all $^
	gcc $(CFLAGS) $^ -o $@


