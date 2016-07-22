#include <stdlib.h>
#include <stdio.h>
#include <netcdf.h>

#define FILE_NAME "test.nc"

#define NDIMS 4
#define NT 24
#define NL 1
#define NX 21
#define NY 21

#define ERRCODE 2
#define ERR(e) {printf("Error: %s\n", nc_strerror(e)); exit(ERRCODE);}

int main()
{
    int ncid, t_dimid, l_dimid, x_dimid, y_dimid, varid;
    int dimids[NDIMS];

    int data[NT][NL][NY][NX];
    int t, x, y, retval;

    for (t = 0; t < NT; t++) {
        for (x = 0; x < NX; x++) {
            for (y = 0; y < NY; y++) {
                data[t][0][x][y] = t + x + y;
            }
        }
    }

    if (retval = nc_create(FILE_NAME, NC_CLOBBER, &ncid)) {
        ERR(retval);
    }

    printf("%d\n", retval, ncid);
}
