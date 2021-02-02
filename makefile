main : run
	
run :
	./run.sh

clean:
	rm *.o out* run

doc:
	slip merge DOCUMENTATION.md > doc.md