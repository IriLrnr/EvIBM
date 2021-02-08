main : run
	
run :
	./run.sh

clean:
	rm *.o out* run

doc:
	slip merge .source_doc.md > DOCUMENTATION.md