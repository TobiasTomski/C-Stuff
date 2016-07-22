#include <stdlib.h>
#include <stdio.h>
#include <netcdf.h>

#define FILE_NAME "/home/t.tomski/C-Stuff/test.nc"

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

    if ((retval = nc_create(FILE_NAME, NC_CLOBBER, &ncid))) {
        ERR(retval);
    }

    if ((retval = nc_def_dim(ncid, "time", NT, &t_dimid))) {
        ERR(retval);
    }

    if ((retval = nc_def_dim(ncid, "level", NL, &l_dimid))) {
        ERR(retval);
    }

    if ((retval = nc_def_dim(ncid, "x", NX, &x_dimid))) {
        ERR(retval);
    }

    if ((retval = nc_def_dim(ncid, "y", NY, &y_dimid))) {
        ERR(retval);
    }

    dimids[0] = t_dimid;
    dimids[1] = l_dimid;
    dimids[2] = x_dimid;
    dimids[3] = y_dimid;

    if ((retval = nc_def_var(ncid, "data", NC_INT, NDIMS, dimids, &varid))) {
        ERR(retval);
    }

    if ((retval = nc_enddef(ncid))) {
        ERR(retval);
    }

    if ((retval = nc_put_var_int(ncid, varid, &data[0][0][0][0]))) {
        ERR(retval);
    }

    if ((retval = nc_close(ncid))) {
        ERR(retval);
    }

    printf("*** [info] SUCCESS writing example file test.nc! ***\n");
    return 0;
}
