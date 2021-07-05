#include "pdfgen.c"
#include<string.h>

int a;

void inttochar(int x, char ch[])
{
    int pin = -1;
    char tmp[1001];
    while (x)
    {
        tmp[++pin] = x % 10 + '0';
        x /= 10;
    }
    for (int i = 0; i <= pin; i++)
    {
        ch[i] = tmp[pin - i];
    }
}

void doubletochar(double x, char ch[])
{
    int pin = -1;
    int tmpint;
    char tmp[1001];
    tmpint = x * 100;
    while (tmpint)
    {
        tmp[++pin] = tmpint % 10 + '0';
        tmpint /= 10;
    }
    for (int i = 0; i <= pin - 2; i++)
    {
        ch[i] = tmp[pin - i];
    }
    ch[pin - 1] = '.';
    ch[pin] = tmp[1];
    ch[pin + 1] = tmp[0];
}

int main(void) 
{
    char ch[101];
    double c = 12345.6789;
    doubletochar (c, ch);

    
    struct pdf_info info = 
    {
        .creator = "My software",
        .producer = "My software",
        .title = "My document",
        .author = "My name",
        .subject = "My subject",
        .date = "Today"
    };
    struct pdf_doc *pdf = pdf_create(PDF_A4_WIDTH, PDF_A4_HEIGHT, &info);
    pdf_set_font(pdf, "Times-Roman");
    pdf_append_page(pdf);
    pdf_add_text(pdf, NULL, ch, 12, 50, 20, PDF_BLACK);
  //  pdf_add_text(pdf, NULL, "%", 12, 100, 820, PDF_BLACK);
//    pdf_add_line(pdf, NULL, 50, 24, 150, 24, 3, PDF_BLACK);
    pdf_save(pdf, "output.pdf");
    pdf_destroy(pdf);
    return 0;
}
