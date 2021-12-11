#include <inttypes.h>
#include <tm4c123gh6pm.h>

uint32_t v[21];
uint32_t count=0x01;
uint32_t v2[21];
uint32_t n=0;
uint32_t i=0;
uint32_t k=0;
uint32_t i;
uint32_t a;
uint32_t b;
uint32_t c;
uint32_t d;
uint32_t e;
uint32_t f;
uint32_t controle;
uint32_t teste=1;
uint32_t count1=1;
uint32_t count2;



void delay(uint32_t delay)
{
    volatile uint32_t elapsedTime;
    uint32_t startTime = NVIC_ST_CURRENT_R;
    do{
        elapsedTime = (startTime-NVIC_ST_CURRENT_R)&0x00FFFFFF;
    }
    while(elapsedTime <= delay);
}
void delay2()
{
    uint32_t time2;
    for(time2=0; time2<10000; time2++){}
}




void AcendeLed(uint32_t ciclos)
{

    for(i=1; i<=ciclos;i++)
    {
        GPIO_PORTB_DATA_R=v[i];
        delay(2000000);
        GPIO_PORTB_DATA_R=0x00;
        delay(1000000);
    }
}

void loop()
{
        count<<1;
        /*if(count>=0x08)
        { count=0x01; }*/
}

void TrataPortF()
{

    k++;
    controle=1;
    delay2();
        if ((GPIO_PORTB_RIS_R & 0x10) == 0x10)  //Verificação de qual pino gerou a inten
        {
            v2[k]=0x01;
            GPIO_PORTB_DATA_R=0x01;
            delay(2000000);
            GPIO_PORTB_DATA_R=0x00;
            delay(2000000);
            GPIO_PORTB_ICR_R=0x10;
        }
        if ((GPIO_PORTB_RIS_R & 0x20) == 0x20)
        {
            v2[k]=0x02;
            GPIO_PORTB_DATA_R=0x02;
            delay(2000000);
            GPIO_PORTB_DATA_R=0x00;
            delay(2000000);
            GPIO_PORTB_ICR_R=0x20;
        }
        if ((GPIO_PORTB_RIS_R & 0x40) == 0x40)
        {
            v2[k]=0x04;
            GPIO_PORTB_DATA_R=0x04;
            delay(2000000);
            GPIO_PORTB_DATA_R=0x00;
            delay(2000000);
            GPIO_PORTB_ICR_R=0x40;
        }
        if ((GPIO_PORTB_RIS_R & 0x80) == 0x80)
        {
            v2[k]=0x08;
            GPIO_PORTB_DATA_R=0x08;
            delay(2000000);
            GPIO_PORTB_DATA_R=0x00;
            delay(2000000);
            GPIO_PORTB_ICR_R=0x80;
        }
}

void main() {




    /*uint32_t var1;
    uint32_t var2;*/
    NVIC_ST_RELOAD_R = 16000000;
    NVIC_ST_CTRL_R = 0x01;
    uint32_t n=0;;
    SYSCTL_RCGCGPIO_R = 0x02;
    //GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTB_LOCK_R = 0x4C4F434B;
    GPIO_PORTB_CR_R = 0xFF;
    GPIO_PORTB_DIR_R = 0x0F;
    //GPIO_PORTF_CR_R = 0xFF;
    GPIO_PORTB_PUR_R = 0xF0;
    GPIO_PORTB_IS_R = 0x00; //Define sensibilidade do botão - 0 borda - 1 sinal continuo
    GPIO_PORTB_IEV_R = 0x00; //Define evento - 0 descida | baixo - 1 subida | alto
    GPIO_PORTB_IBE_R = 0x00; //Define inten por ambas as bordas
    GPIO_PORTB_IM_R = 0xF0; //Habilita inten no pino
    GPIO_PORTB_DEN_R = 0xFF ;
    NVIC_EN0_R = 0x02;//habilita inten do portF

    while(1)
    {

            v[1]=0x01;


        if(n==0){AcendeLed(1); n++; controle=1;}
        for(c=1; c<=3; c++)
        {
            if(n==c)
            {
                b=0;
                f=0;
                while(controle==1){
                count1++;
                if(count1>5){ count1=1; }
                switch(count1)
                {
                case 1:
                    count2=0x01;
                    break;
                case 2:
                    count2=0x02;
                    break;
                case 3:
                    count2=0x04;
                    break;
                case 4:
                    count2=0x08;
                    break;
                }
                for(a=1; a<=c; a++)
                {
                    if((v[a]==v2[a]) & (k==c))
                    {
                        b++;
                    }
                    if((v[a]!=v2[a]) & (k==c))
                    {
                        f++;
                    }
                    if(k>c)
                    {
                        f++;
                    }
                }
                if(f>0)
                {
                    GPIO_PORTB_DATA_R=0x0F;
                    delay(4000000);
                    GPIO_PORTB_DATA_R=0x00;
                    delay(4000000);
                    ResetISR();
                }
                if(b==c)
                {
                    controle=0;
                    v[c+1]=count2;
                    AcendeLed(c+1);
                    n++;
                    f=0;
                    k=0;
                }}
            }
        }
        if(n==4)
        {
            b=0;
            f=0;
            for(a=1; a<=4; a++)
            {
                if((v[a]==v2[a]) & (k==4))
                {
                     b++;
                }
                if((v[a]!=v2[a]) & (k==4))
                {
                     f++;
                }
                if(k>4)
                {
                    f++;
                }
            }
            if(f>0)
            {
                GPIO_PORTB_DATA_R=0x0F;
                delay(4000000);
                GPIO_PORTB_DATA_R=0x00;
                delay(4000000);
                ResetISR();
            }
            if(b==4){ GPIO_PORTB_DATA_R=0x06; delay(4000000); }
        }
    }
}
