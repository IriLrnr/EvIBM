main : run
	
run :
	./run.sh

clean:
	rm *.o out* run

doc:
	merge slip merge DOCUMENTATION.md > doc.md