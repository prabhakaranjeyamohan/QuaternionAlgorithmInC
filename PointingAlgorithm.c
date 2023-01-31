#include <stdio.h>
#include <stdlib.h>
#include <math.h>



float Ar(float x, float y , float z, float pitch, float roll, float yaw)
{
    yaw = 0;
    float Ar = ((-y * cos(yaw)) * cos(roll)) + (x*sin(yaw)*cos(roll)) - (z*cos(pitch)*sin(roll)) - (x*cos(yaw)*sin(pitch)*sin(roll)) - (y*sin(yaw) * sin(pitch)* sin(roll));
    return Ar;
}
float Br(float x, float y, float z, float pitch, float roll, float yaw)
{
    yaw=0;
    float Br = (z*cos(pitch)*cos(roll)) - (y*cos(yaw)*sin(roll))+ (x*sin(yaw)*sin(roll)) + (x*cos(yaw)*sin(pitch)*cos(roll)) + (y*sin(yaw)*sin(pitch)*cos(roll));
    return Br;

}
float Ap(float x, float y , float z, float pitch, float yaw)
{
    yaw = 0;
    float Ap = (-z*sin(pitch)) + (x*cos(yaw) * cos(pitch)) + (y*sin(yaw)*cos(pitch));
    return Ap;
}

float Bp(float x, float y , float z, float pitch, float yaw)
{
    yaw = 0;
    float Bp = (powf(z,2) * (cos(pitch) *cos(pitch))) + ((powf(y,2) * (cos(yaw) * cos(yaw))) + ((powf(x,2) * sin(pitch) * cos(yaw) * cos(yaw))) + (y*z*sin(yaw) *sin(2*pitch)) + ((powf(x,2) * sin(yaw) * sin(yaw))) + ((pow(y,2) * sin(pitch) * sin(pitch)) * sin(yaw) * sin(yaw))) + (x*z*cos(yaw) * sin(2*pitch)) - (2*x*y*sin(yaw)*cos(yaw)) + (x*y*sin(pitch) * sin(pitch)*sin(2*yaw));
    return Bp;
}





int main()
{
   float yaw=0;
    float lat, cosLat, sinLat;
    float lon;
    float alt;

    printf("Enter the latitude of the turret in degree: ");
    scanf("%f", &lat);
    printf("Enter the longitude of the turret in degree : ");
    scanf("%f", &lon);
    printf("Enter the altitude of the turret in metre : ");
    //Altitude is the height from the planatory ellipsoid obatained from a GPS.
    //Please make sure the GPS uses WGS-84 model
    scanf("%f", &alt);

    //convert degree to radians
    float latRad = lat * (M_PI / 180.0);
    float lonRad = lon * (M_PI / 180.0);


    float rad = 6378137.0;
    //Radius of the Earth
    float f = 1.0/298.257223563;
    


    cosLat = cos(latRad);
    sinLat = sin(latRad);


    float FF = powf((1.0-f),2);
    float C = 1/sqrt((powf(cosLat,2) + FF * powf(sinLat,2)));
    float S = C * FF;

    float xs = (rad * C + alt) * cosLat * cos(lonRad);
    float ys = (rad * C + alt) * cosLat * sin(lonRad);
    float zs = (rad * S + alt) * sinLat;

    printf("%f \n", xs is the ECEF x co-ordinate of the ship);
    printf("%f \n", ys is the ECEF y co-ordinate of the ship);
    printf("%f \n", zs is the ECEF z co-ordinate of the ship);
    


    float xt, yt , zt ;

    printf("X co-ordinate of drone (ECEF) : ");
    scanf("%f", &xt);
    printf("Y co-ordinate of drone (ECEF) : ");
    scanf("%f", &yt);
    printf("Z co-ordinate of drone (ECEF) : ");
    scanf("%f", &zt);


    float pitch, roll ;


    printf("Enter the pitch value of the ship in degree : ");
    scanf("%f", &pitch);
    printf("Enter the roll value of the ship in degree : ");
    scanf("%f", &roll);

    pitch = pitch * (M_PI/180.0);
    roll = roll * (M_PI/180);


    float x = xt-xs;
    float y = yt-ys;
    float z = zt-zs;

    // Equation 15 and 16 from the paper

float azimuth = atan(Ap(x,y,z,pitch,yaw) /Bp(x,y,z,pitch,yaw));
azimuth = azimuth * (180/M_PI);

float elevation = atan(Ar(x,y,z, pitch, roll,yaw)/Br(x,y,z,pitch,roll,yaw));
elevation = elevation * (180/ M_PI);

printf("%f is the required azimuth angle in degree" , azimuth);
printf("\n %f is the required elevation angle in degree", elevation);
}
