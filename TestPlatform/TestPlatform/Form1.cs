using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;

namespace TestPlatform
{
    public partial class Form1 : Form
    {
        bool HexStringInsertBlankFlag = false;
        bool ProgressStartFlag = false;             //进度条演示启停控制
        UInt16 progress1MaxVal = 300;               //进度条1最大值
        UInt16 progress2MaxVal = 200;               //进度条2最大值
        UInt16 progress3MaxVal = 100;               //进度条3最大值
        public Form1()
        {
            InitializeComponent();
            ProgressBar1Disp(true, progress1MaxVal);//设置进度条最大值
            ProgressBar2Disp(true, progress2MaxVal);//设置进度条最大值
            ProgressBar3Disp(true, progress3MaxVal);//设置进度条最大值
            ThreadsStart();                         //启动线程
        }


        #region //委托
        private delegate void dispProgressBar1(bool SetMaxVal, UInt16 Value);           //委托

        private void ProgressBar1Disp(bool SetMaxVal, UInt16 Value)                     //实现进度条控制
        {
            //if (this.InvokeRequired)
            if (this.progressBar1.InvokeRequired)
            {
                dispProgressBar1 disp = new dispProgressBar1(ProgressBar1Disp);
                this.Invoke(disp, new object[] { SetMaxVal, Value });
            }
            else
            {
                if (SetMaxVal == true) progressBar1.Maximum = Value;
                else progressBar1.Value = Value;
            }
        }
        private delegate void dispProgressBar2(bool SetMaxVal, UInt16 Value);           //委托

        private void ProgressBar2Disp(bool SetMaxVal, UInt16 Value)                     //实现进度条控制
        {
            if (this.InvokeRequired)
            //if (this.progressBar2.InvokeRequired)
            {
                dispProgressBar2 disp = new dispProgressBar2(ProgressBar2Disp);
                this.Invoke(disp, new object[] { SetMaxVal, Value });
            }
            else
            {
                if (SetMaxVal == true) progressBar2.Maximum = Value;
                else progressBar2.Value = Value;
            }
        }
        private delegate void dispProgressBar3(bool SetMaxVal, UInt16 Value);           //委托

        private void ProgressBar3Disp(bool SetMaxVal, UInt16 Value)                     //实现进度条控制
        {
            if (this.InvokeRequired)
            //if (this.progressBar3.InvokeRequired)
            {
                dispProgressBar3 disp = new dispProgressBar3(ProgressBar3Disp);
                this.Invoke(disp, new object[] { SetMaxVal, Value });
            }
            else
            {
                if (SetMaxVal == true) progressBar3.Maximum = Value;
                else progressBar3.Value = Value;
            }
        }
        #endregion

        #region ///线程启动
        /// <summary>
        /// 所有线程启动的地方
        /// </summary>
        private void ThreadsStart()
        {
            //测试线程
            Thread TestThread = new Thread(new ThreadStart(FuncTestThread));
            TestThread.IsBackground = true;
            TestThread.Name = "TestThread";
            TestThread.Start();
        }
        #endregion

        #region///测试线程
        private void FuncTestThread()
        {
            UInt16 progress1Val = 0;//进度条1当前值
            UInt16 progress2Val = 0;//进度条2当前值
            UInt16 progress3Val = 0;//进度条3当前值
            Thread.Sleep(100);
            while (true)
            {
                if (ProgressStartFlag == true)
                {
                    progress1Val++; //进度条1当前值++
                    progress2Val++; //进度条2当前值++
                    progress3Val++; //进度条3当前值++
                }
                if (progress1Val > progress1MaxVal) progress1Val = 0;
                if (progress2Val > progress2MaxVal) progress2Val = 0;
                if (progress3Val > progress3MaxVal) progress3Val = 0;
                ProgressBar1Disp(false, progress1Val);                  //进度条1当前值更新到控件
                ProgressBar2Disp(false, progress2Val);                  //进度条2当前值更新到控件
                ProgressBar3Disp(false, progress3Val);                  //进度条3当前值更新到控件
                Thread.Sleep(10);
            }
        }
        #endregion





        #region ///功能函数
        //字符串转换为16进制字节数组
        private byte[] TranslateStringToHexArray(string AsciiString)
        { 
            int cnt = 0;
            string inputAsciiArray= "";
            //1、将字符串按每两个字符拆分并插入逗号为分隔符
            for (int i = 0; i < AsciiString.Length; i++)
            {
                char temp = AsciiString[i];
                if(temp!=' ')
                {
                    inputAsciiArray += temp;
                    cnt++;
                    if (cnt >= 2)
                    {
                        cnt = 0;
                        inputAsciiArray += ",";
                    }
                }
            }
            //2、将拆分后的字符串分离为字符串数组
            string[] bStringArray = inputAsciiArray.Split(new char[] { ',', ' ' });
            cnt=0;
            for (int i = 0; i < bStringArray.Length; i++)
            {
                if (bStringArray[i].Trim() != "") cnt++;
            }
            byte[] bArray1=new byte[cnt];
            cnt = 0;
            //3、将字符串数组转换成字节数组并检测字符是否合法
            for (int i = 0; i < bStringArray.Length; i++)
            {
                if (bStringArray[i].Trim() != "")
                {
                    try
                    {
                        bArray1[i] = Convert.ToByte(bStringArray[i].Trim(), 16);
                        cnt++;
                    }
                    catch (Exception E)     //发生错误时提示非法字符
                    {
                        //string ErrMsg = " " + bStringArray[i] + " " + E.Message;
                        string ErrMsg = " 第 " +(i*2+1).ToString() + " 个字符 "+ bStringArray[i] +" 非法 \r\n" + E.ToString();
                        MessageBox.Show(ErrMsg, "提示");
                        break;
                    }
                }
            }
            //4、将合法转换后的字节数组输出
            byte[] bArray2 = new byte[cnt];
            for (int i = 0; i < cnt; i++)
            { 
                bArray2[i]=bArray1[i];
            }
            return bArray2;
        }

        //字节数组转换为字符串
        private string TranslateHexArrayToString(byte[] InputByteArray,bool AddBlankFlag)
        {
            string HexString = "";
            if (AddBlankFlag == true)   //确定是否需要插入特殊符号                
            {
                for (int i = 0; i < InputByteArray.Length; i++)
                {
                    HexString += InputByteArray[i].ToString("X2")+ " ";     //字节数据转换为字符（并插入空格）
                }
            }
            else                         //字符串终字节间不插入空格 
            {
                for (int i = 0; i < InputByteArray.Length; i++)
                {
                    HexString += InputByteArray[i].ToString("X2");          //字节数据转换为字符
                }
            }
            return HexString;
        }

        #endregion

        #region ///界面处理

        private void btnAsciiToHEX_Click(object sender, EventArgs e)
        {
            string inputAsciiArray = textBoxInputAscii.Text.Trim();
            byte[] temp=TranslateStringToHexArray(inputAsciiArray);
            string strTemp = TranslateHexArrayToString(temp, HexStringInsertBlankFlag);
            textBoxOutput.Text = strTemp;

            //ProgressBar1Disp(false, 50);
        }

        private void checkBoxInsertBlank_CheckedChanged(object sender, EventArgs e)
        {
            HexStringInsertBlankFlag = checkBoxInsertBlank.Checked;
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            Environment.Exit(0);
        }

        private void checkBoxStart_CheckedChanged(object sender, EventArgs e)
        {
            ProgressStartFlag = checkBoxStart.Checked;
            if (ProgressStartFlag == false)
            {
                checkBoxStart.Text = "继续";
            }
            else
            {
                checkBoxStart.Text = "停止";
            }
        }
        #endregion


    }
}
