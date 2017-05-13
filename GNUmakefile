test: build
	perl -Mblib -MYAML::LibYAML::Emitter \
	    -wE 'print YAML::LibYAML::Emitter::test()'

build: libyaml
	perl Makefile.PL
	make -f Makefile

clean:
	rm -fr libyaml

purge:
	make -f Makefile $@

libyaml:
	git clone git@github.com:yaml/libyaml
	( \
	    cd libyaml; \
	    ./bootstrap && \
	    ./configure && \
	    make \
	)

