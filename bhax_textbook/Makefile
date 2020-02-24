all:	clean fdl

fdl:	clean validate_bhax-textbook_fdl_hu bhax-textbook_fdl.pdf
	
bhax-textbook_fdl.pdf: bhax-textbook-fdl.xml bhax-textbook.xls
	dblatex bhax-textbook-fdl.xml -p bhax-textbook.xls
	
.PHONY: validate_bhax-textbook_fdl_hu
validate_bhax-textbook_fdl_hu:
	wget -O schema.rng http://docbook.org/xml/5.0/rng/docbookxi.rng
	xmllint --xinclude bhax-textbook-fdl.xml --output output.xml
	xmllint --noout --relaxng schema.rng output.xml
	rm -f output.xml schema.rng
	
.PHONY: clean
clean:
	rm -f bhax-textbook-fdl.pdf
