#include "calculate.h"

Calculate::Calculate()
{

}

Calculate::~Calculate()
{

}
bool Calculate::firstcalCulate()
{
    double sum = 0;
    int digt = 0;
    double temp;
    int sig_count=0;
    int sig_flag = 0;
    QVector<QString>::iterator iter0 = data.begin();
    if(*iter0 == "-"|| *iter0 == ".")
    {
        data.push_front("0");//如果最开头输入的是小数点或负号，那么在前面加一个零
                             //如果是小数点的话，即为0.x
                             //如果是-号的话，即为0-x=-x
    }

    for(QVector<QString>::iterator iter = data.end() - 1; iter >= data.begin(); iter--)
    {
        if(*iter == ".")
        {
            sig_flag++;  //判断多个小数点
        }
        if(*iter !=data.begin())
        if(*iter=="."&&*(iter-1)==".")  //判断连续小数点，如果小数点是连续的话，直接错误，要求重新输入表达式
        {

            return false;
        }

        if( *iter!="+" && *iter!="-" && *iter!="*" && *iter!="/" && *iter!=")" && *iter!="(" )//字符转数
        {
            sig_count = 0;
            if(*iter!=".")//将小数点前后的数字合成一位，因为0.5其实是三个字符，而不是一个数字
            {
                bool ok;
                temp = iter->toInt(&ok,10);
                temp = temp * qPow(10,digt);//字符转数
                sum = sum + temp;
                digt++;
            }
            else
            {
                double a = qPow(10,0-digt);
                sum = sum * a;
                digt = 0;
            }

        }
        if(*iter=="+"||*iter=="-"||*iter=="*"||*iter=="/"||iter==data.begin()||*iter==")"||*iter=="(")
        {

            sig_flag = 0;
            sig_count++;
            if(sig_count==1)
            {
                tempdata.push_front(QString::number(sum));//数转字符
                sum = 0;
                digt = 0;
            }
           if(*iter=="+"||*iter=="-"||*iter=="*"||*iter=="/"||*iter==")"||*iter=="(")
           {
                tempdata.push_front(*iter);
                if(*iter == "-" && *(iter-1) == "(")
                {
                    tempdata.push_front("0");
                }
           }
        }
        if(sig_flag > 1)
        {
            return false;
        }

    }
return true;
}

bool Calculate::secondCalculate() //中缀转后缀，逆波兰式
{
    int gradeTop;//栈内优先数
    int grade;//栈外优先数

    for(QVector<QString>::iterator iter = tempdata.end() - 1; iter >= tempdata.begin(); iter--)
    {

      if(*iter!="+"&&*iter!="-"&&*iter!="*"&&*iter!="/"&&*iter!=")"&&*iter!="(")
      {
          data3.push(*iter); //操作数直接进栈
      }
      else if(*iter=="+"||*iter=="-"||*iter=="*"||*iter=="/")
      {        //设置栈外优先数
          if(*iter=="+"||*iter=="-")
          {
             grade = 1;
          }
          if(*iter=="*"||*iter=="/")
          {
              grade = 2;
          }
          while (1) {

              if(data2.empty()||data2.top()==")")
              {
                  data2.push(*iter);
                  break;
              }

              if(data2.top()=="+"||data2.top()=="-") // 设置栈外优先数
              {
                 gradeTop = 1;
              }
              if(data2.top()=="*"||data2.top()=="/")
              {
                  gradeTop = 2;
              }

              if(data2.empty()||data2.top()==")")
              {
                  data2.push(*iter);
                  break;
              }
               if(grade>=gradeTop)   //比较栈内优先数和栈外优先数，如果grade>=topgrade就压栈
              {
                  data2.push(*iter);
                  break;
              }
              else
              {
                  data3.push(data2.pop());    //如果data2栈顶操作符优先数topgrade高于grade就出栈并压入data3
              }
          }

      }
      else if(*iter==")")
      {
          data2.push(*iter);  //遇到右括号直接压入data2
      }
      else if(*iter=="(")
      {
          if(data2.length() == 0)
          {
              return false;
          }
          while(data2.top()!=")")
          {
              data3.push(data2.pop());//遇到左括号时在便利到右括号前将遇到的所有data2中的操作符压入data3
          }
         data2.pop();// 将左括号出栈
      }
    }
    while(!data2.empty())
    {
        data3.push(data2.pop());
    }

   while(!data3.empty())
   {
       if(data3.top() == ")")
       {
           return false;
       }
       data2.push(data3.pop());//经过两次转换，现在data2中存放正确顺序的后缀表达式

   }
   return true;
}

QString Calculate::ThirdCalculate(QString& qwe)   //后缀计算，即先出栈两个数字，然后出栈一个字符，进行相加计算
{
    while(!data2.empty())
    {
        if(data2.top()!="+" && data2.top()!="-" &&data2.top()!="*" &&data2.top()!="/" )
        {
            data3.push(data2.pop());
            continue;
        }
        if(data3.length()==1)
        {
            if(data2.top() == "+" || data2.top() == "-" || data2.top() == "*" || data2.top() == "/")
            {
                return "错误";//如果只有一个数字供操作，肯定是错误的
            }
        }

        switch (*data2.pop().toLatin1().data())
        {
        case '+':
            data3.push(QString::number(data3.pop().toDouble() + data3.pop().toDouble()));
            break;
        case '-':
            data3.push(QString::number(data3.pop().toDouble() - data3.pop().toDouble()));
            break;
        case '*':
            data3.push(QString::number(data3.pop().toDouble() * data3.pop().toDouble()));
            break;
        case '/':
            data3.push(QString::number(data3.pop().toDouble() / data3.pop().toDouble()));
            break;
        default:
            break;
        }
    }
    QString tmp = data3.top();
    clearVector();
    data.push_back(tmp);
    qwe=tmp;
    return tmp;

}
void Calculate::clearVector()
{
    data.clear();
    tempdata.clear();
    data2.clear();
    data3.clear();

}


