main : run

run :
	./run.sh

clean:
	rm -f *.o out* run

doc:
	slip merge .source_doc.md > DOCUMENTATION.md