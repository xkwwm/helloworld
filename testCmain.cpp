#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <string>
#include <map>
#include <iterator>
#include <vector>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <math.h>
#include <iconv.h>
#include "Calculator.h"

#define BUFFLEN 1024
#define WAIT_STAR 4
#define GET_IP_SUCC 20
#define DSTR_BEGIN 5
#define DSTR_END 21
#define FINISH 8
#define WAIT_FINISH 22
#define TASK_FAIL 6
#define MANUAL_END 9
#define MANUAL_END_FIN 10

using namespace std;

int calNowAngel()
{
	  string angelTime;
    double max = 1.0;
    double min = 0.999987;
    int iRecoverFlag=0;
   
    //getMaxAndMin(cTask,mapHis, mapNow, max , min);//获取曲线线段最大值最小值
    double yesterday_angel_n = -1;
        int iCount=0;
        vector<double> y1Vector;//告警当天数据
        vector<double> y2Vector;//告警1天前数据

        y1Vector.push_back(1.0);
        y1Vector.push_back(1.0);
        y1Vector.push_back(1.0);
        y1Vector.push_back(1.0);
        y1Vector.push_back(1.0);
        y1Vector.push_back(1.0);
        y1Vector.push_back(1.0);
        y1Vector.push_back(1.0);
        y1Vector.push_back(1.0);
        
        y2Vector.push_back(1.0);
        y2Vector.push_back(1.0);
        y2Vector.push_back(1.0);
        y2Vector.push_back(1.0);
        y2Vector.push_back(1.0);
        y2Vector.push_back(1.0);
        y2Vector.push_back(1.0);
        y2Vector.push_back(1.0);
        y2Vector.push_back(1.0);
        int n=9;
        //2.1 0-1标准化 
        if(max >= min)
        {
            for(int i = 0; i<n; ++i)
            {
            	  if( (max-min)<0.0000001 && (max-min)>-0.0000001 ) {
            	  	 y1Vector[i]=0;
            	  } else {
                   y1Vector[i] = (y1Vector[i] - min)/(max - min);
                }
            }
            for(int i = 0; i<n; ++i)
            {
            	  if( (max-min)<0.0000001 && (max-min)>-0.0000001 ) {
            	  	 y2Vector[i] = 0;
            	  } else {
                   y2Vector[i] = (y2Vector[i] - min)/(max - min);
                }
            }

            vector<double> xVector;
            double delt = 1.0 / n;
            for(int i=1; i<=n ; ++i)
            {
                xVector.push_back(delt * i);
            }
    
            //2.2两条直线拟合
            double x_sum = 0;
            double y1_sum = 0;
            double y2_sum = 0;
            double x_2_sum = 0;
            double x_y1_sum = 0;
            double x_y2_sum = 0;
            for(int i = 0; i<n; ++i)
            {
                double x = xVector[i];
                double y1 = y1Vector[i];
                double y2 = y2Vector[i];

                x_sum += x;
                y1_sum += y1;
                y2_sum += y2;
                x_2_sum += (x * x);
                x_y1_sum += (x * y1);
                x_y2_sum += (x * y2);
            }

            double k1 = (n * x_y1_sum - x_sum * y1_sum) / (x_2_sum * n - x_sum * x_sum);
            double k2 = (n * x_y2_sum - x_sum * y2_sum) / (x_2_sum * n - x_sum * x_sum);

            //2.3求曲线夹角
            double tansitan1_2 = fabs((k2 - k1) / (1 + k1 * k2));
            yesterday_angel_n = atan(tansitan1_2) * 180 / M_PI;//这个就是最终夹角结果

            printf("n=%d linear fit k1[%f] k2[%f]yesterday_angel_n[%f] max[%f] min[%f]\n", n, k1 , k2 , yesterday_angel_n, max ,min);
            if(isnan(yesterday_angel_n) != 0)
            {
                yesterday_angel_n = -1;
            }
        }
        else
        {
            printf("n=%d linear fit max <= min\n", n);
            yesterday_angel_n = -1;
            //lastweek_angel_n = -1;
        }

	  return 0;
}


main(int argc, char *argv[]) 
{
  
   calNowAngel();
   	 
}