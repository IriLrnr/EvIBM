#include "species.h"

void Write_Data (FILE **, FILE **, FILE**, FILE **, int*, int, int, int, Population, Parameters); 

void Open_Files (FILE **, FILE **, FILE **, FILE **, FILE **, Parameters, int);

void Reopen_Files (FILE **, FILE **, FILE **, FILE **, Parameters, int);

void Close_Files (FILE **, FILE **, FILE **, FILE **);

void Write_Distance_Data (FILE **, Population, int, int, Parameters);

void Read_Data (FILE **, FILE **, Population, Parameters);