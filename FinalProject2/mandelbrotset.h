#ifndef __MANDELBROTSET_H__
#define __MANDELBROTSET_H__
#include"defs.h"
#include<math.h>
const double pi=22/7;
int iter=85;
typedef struct _complex_s1
{
    double r;
    double i;
}complex;
complex sum(complex a,complex b)
{
    complex s1;
    s1.r=a.r+b.r;
    s1.i=a.i+b.i;
    return s1;
}
complex zarb(complex a,complex b)
{
    complex s1;
    s1.r=a.r*b.r-a.i*b.i;
    s1.i=a.i*b.r+a.r*b.i;
    return s1;
}
double mot(complex a)
{
    return sqrt(a.r*a.r + a.i*a.i);
}

int get_mbs_iter(double x, double y)
{
    complex c={x,y};
    complex s1={0,0};
    int n=0;
    while(mot(s1) <= 2 && n<iter)
    {
        s1=sum(zarb(s1,s1),c);
        n++;
    }
    return n;
}

void hsv_to_rgb(int hue, int min, int max, COLORINDEX* p)
{
    // TODO
    // p->g=hue;
    // p->b=hue;
    // p->r=hue;
}

void UpdateImageData(ImageState* state)
{
    for(int x=0; x<state->width; x++)
    {
        for(int y=0; y<state->height; y++)
        {
            double dx=state->minx+((double)x/state->width)*(state->maxx-state->minx);
            double dy=state->miny+((double)y/state->height)*(state->maxy-state->miny);
            // x,y => dx,dy
            // dx,dy => rx, ry
            double rx = dx * cos(state->angle) + dy * sin(state->angle);
            double ry = -dx * sin(state->angle) + dy * cos(state->angle);

            int iter = get_mbs_iter(rx, ry);
            state->bmFileData.bmData[(y * state->width + x)*COLORBYTES] = iter;
        }
    }
    for(int i=0; i<256; i++)
    {
        int hue = (int) ((i / 255)/360);
        hsv_to_rgb(hue, 110, 260, &(state->bmFileData.bmHeader.colorIdx[i]));
        if (iter<85)
        {
            state->bmFileData.bmHeader.colorIdx[i].r=1;
        }
        if(iter>85)
        {
            state->bmFileData.bmHeader.colorIdx[i].r=2;
        }
        // state->bmFileData.bmHeader.colorIdx[i].r=i;
        // state->bmFileData.bmHeader.colorIdx[i].g=i;
        // state->bmFileData.bmHeader.colorIdx[i].b=i;

    }
    state->bmFileData.bmHeader.colorIdx[1].r=44;
    state->bmFileData.bmHeader.colorIdx[2].b=210;

    
}

void ChangeCenter(ImageState* state, double newcx, double newcy, int steps)
{
    double x=(newcx - state -> cx)/steps;
    double y=(newcy - state -> cy)/steps;
    for(int i=0;i<steps; i++)
    {
        state ->cx+=x;
        state ->cy+=y;
        state ->minx+=x;
        state ->maxx+=x;
        state ->miny+=y;
        state ->maxy+=y;

        UpdateImageData(state);
        WriteBitmapFile(state->image_count++, & state->bmFileData);
    }
}

void ChangeZoom(ImageState* state, double zoom, int steps)
{
    double zoomba=pow(zoom,1./steps);
    for(int i=0; i<steps; i++)
    {
        double dix=state->maxx - state->minx;
        double diy=state->maxy - state->miny;
        double dx= dix - dix/zoomba;
        double dy = diy - diy/zoomba;
        state->minx=state->minx+dx/2;
        state->maxx=state->maxx-dx/2;
        state->miny=state->maxy+dy/2;
        state->maxy=state->maxy-dy/2;
        UpdateImageData(state);
        WriteBitmapFile(state->image_count++, & state->bmFileData);
    }
}

void ChangeRotation(ImageState* state, double angle, int steps)
{
    state->angle=(state->angle)*(pi/180);
    double angle_step = angle / steps;
    for(int i=0; i<steps; i++)
    {
        state->angle += angle_step;
        UpdateImageData(state);
        WriteBitmapFile(state->image_count++, & state->bmFileData);
    }
}

void Hold(ImageState* state, int steps)
{
    // TODO
    double hold_step = steps;
    for(int i=0; i<steps; i++)
    {
        state->minx=state->minx;
        state->miny=state->miny;
        state->minx=state->maxx;
        state->minx=state->maxy;
        WriteBitmapFile(state->image_count++, & state->bmFileData);
    }
}

#endif