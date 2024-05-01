#include "ppmUtil.h"

void writeHeader(FILE* image, header_t head)
{
    fprintf(image, "%s %d %d %d\n", head.type, head.width, head.height,  
                                    head.maxVal);
}
void writePixels(FILE* image,pixel_t* p, header_t head)
{
    int howManyPixels = head.width * head.height;
    fwrite(p, howManyPixels, sizeof(pixel_t), image);
}

pixel_t* readPixels(FILE* image, header_t head)
{
    pixel_t* pix = allocatePixMemory(head);
    fread(pix, head.height*head.width, sizeof(pixel_t), image);

    return pix;

}

pixel_t* read(FILE* in, header_t *head)
{
    readHeader(in, head);
    pixel_t* pix = readPixels(in, *head);
    return pix;
}
void write(FILE* image, header_t head, pixel_t* pix)
{
    writeHeader(image, head);
    writePixels(image, pix, head);

}

pixel_t* allocatePixMemory(header_t h)
{
    pixel_t* pixel = malloc((h.width*h.height)*sizeof(pixel_t)); 
    return pixel;
}

void ckComment(FILE* in)
{
    unsigned int wscm = fgetc(in);
   /*read as long whitespace or comment*/
   while(wscm == '#' || isspace(wscm)) 
   {
      /*checks for whitespace*/
      if(isspace(wscm)) 
      {
         /*read as long as ws*/
         while (isspace(wscm)) 
         {
            wscm = fgetc(in);
         }
         ungetc(wscm,in);
      }
      /*checks for comments*/
      if (wscm == '#') 
      {

         /*read as long as comm or not ws*/
         while (wscm == '#' || wscm != '\n') 
         {
            wscm = fgetc(in);
         }
      }
    wscm = fgetc(in);
   }
   ungetc(wscm,in);
}

void readHeader(FILE* in, header_t *hdr)
{   
    fscanf(in, "%s", hdr->type);
    ckComment(in);
    fscanf(in, "%d", &hdr->width);
    ckComment(in);
    fscanf(in, "%d", &hdr->height);
    ckComment(in);
    fscanf(in, "%d\n", &hdr->maxVal);  
    ckComment(in);
}

void freeMemory(pixel_t* pix)
{
    free(pix);
}