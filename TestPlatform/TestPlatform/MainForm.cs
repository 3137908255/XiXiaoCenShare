using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.IO;
using ComXYZ;
namespace TestPlatform
{
    public partial class MainForm : Form
    {
        #region ///控制台开关控制定义
        bool ConsoleWindowOpenFlag = false;
        bool listBoxLogAddTimeFlag = false;
        [DllImport("kernel32.dll")]
        public static extern Boolean AllocConsole();    //显示控制台
        [DllImport("kernel32.dll")]
        public static extern Boolean FreeConsole();     //释放控制台、关闭控制台
        #endregion
        #region                                         //串口相关变量
        ComY comY1 = new ComY();
        Queue ComRxDataQueue = new Queue();             //串口接收数据队列
        string ComName = "";
        int ComBps = 0;
        #endregion
        #region //文件相关定义
        string CurrentLogFilePath = "";

        #endregion
        #region                                         //字典定义
        DateTime StartTime = new DateTime();
        DateTime FinishTime = new DateTime();
        const int IoItemAmount = 64;
        Dictionary<int, string> DictionaryIO = new Dictionary<int, string>();
        #endregion
        #region //命令定义
        byte cmdLineNum, para;
        const string logDataFormat = "ReceiveData";
        bool DeviceConnectFlag = false;
        byte ProFrameHead = 0x4B, ProFrameEnd = 0xB4;
        const byte PRO_CMD_CONNECT = 0x01;                  //联机
        const byte PRO_CMD_FB_CONNECT = 0x02;               //联机反馈
        const byte PRO_CMD_MONITOR_VAR_BIT = 51;                  //监控命令
        #endregion
        #region //系统启动
        public MainForm()
        {
            InitializeComponent();
            this.MaximizeBox = false;
            //this.MinimizeBox = false;
            comboBoxComBps.SelectedIndex = 0;
            SystemStartUI_EnableSet();
            DispConnectedImage(false);
            InitDictionaryIO(IoItemAmount);
            CheckBoxTextInit();
            RenewDictionaryKeyToUI();
            ThreadsStart();
            FreeConsole();
            RenewCfgFileList();
            //DecodeCfgFile();
            RenewDictionaryKeyToUI();
            DispComNameList();
            listBoxReceiceLog.Items.Clear();
            listBoxReceiceLog.Items.Add(" --------- 监控日志 --------- ");
        }

        private void CheckBoxTextInit()
        {
            int i = 1;
            G1checkBox1.Text = "Item" + i.ToString(); i++;
            G1checkBox2.Text = "Item" + i.ToString(); i++;
            G1checkBox3.Text = "Item" + i.ToString(); i++;
            G1checkBox4.Text = "Item" + i.ToString(); i++;
            G1checkBox5.Text = "Item" + i.ToString(); i++;
            G1checkBox6.Text = "Item" + i.ToString(); i++;
            G1checkBox7.Text = "Item" + i.ToString(); i++;
            G1checkBox8.Text = "Item" + i.ToString(); i++;
            i = 1;
            G2checkBox1.Text = "Item" + i.ToString(); i++;
            G2checkBox2.Text = "Item" + i.ToString(); i++;
            G2checkBox3.Text = "Item" + i.ToString(); i++;
            G2checkBox4.Text = "Item" + i.ToString(); i++;
            G2checkBox5.Text = "Item" + i.ToString(); i++;
            G2checkBox6.Text = "Item" + i.ToString(); i++;
            G2checkBox7.Text = "Item" + i.ToString(); i++;
            G2checkBox8.Text = "Item" + i.ToString(); i++;
            i = 1;
            G3checkBox1.Text = "Item" + i.ToString(); i++;
            G3checkBox2.Text = "Item" + i.ToString(); i++;
            G3checkBox3.Text = "Item" + i.ToString(); i++;
            G3checkBox4.Text = "Item" + i.ToString(); i++;
            G3checkBox5.Text = "Item" + i.ToString(); i++;
            G3checkBox6.Text = "Item" + i.ToString(); i++;
            G3checkBox7.Text = "Item" + i.ToString(); i++;
            G3checkBox8.Text = "Item" + i.ToString(); i++;
            i = 1;
            G4checkBox1.Text = "Item" + i.ToString(); i++;
            G4checkBox2.Text = "Item" + i.ToString(); i++;
            G4checkBox3.Text = "Item" + i.ToString(); i++;
            G4checkBox4.Text = "Item" + i.ToString(); i++;
            G4checkBox5.Text = "Item" + i.ToString(); i++;
            G4checkBox6.Text = "Item" + i.ToString(); i++;
            G4checkBox7.Text = "Item" + i.ToString(); i++;
            G4checkBox8.Text = "Item" + i.ToString(); i++;
            i = 1;
            G5checkBox1.Text = "Item" + i.ToString(); i++;
            G5checkBox2.Text = "Item" + i.ToString(); i++;
            G5checkBox3.Text = "Item" + i.ToString(); i++;
            G5checkBox4.Text = "Item" + i.ToString(); i++;
            G5checkBox5.Text = "Item" + i.ToString(); i++;
            G5checkBox6.Text = "Item" + i.ToString(); i++;
            G5checkBox7.Text = "Item" + i.ToString(); i++;
            G5checkBox8.Text = "Item" + i.ToString(); i++;
            i = 1;
            G6checkBox1.Text = "Item" + i.ToString(); i++;
            G6checkBox2.Text = "Item" + i.ToString(); i++;
            G6checkBox3.Text = "Item" + i.ToString(); i++;
            G6checkBox4.Text = "Item" + i.ToString(); i++;
            G6checkBox5.Text = "Item" + i.ToString(); i++;
            G6checkBox6.Text = "Item" + i.ToString(); i++;
            G6checkBox7.Text = "Item" + i.ToString(); i++;
            G6checkBox8.Text = "Item" + i.ToString(); i++;
            i = 1;
            G7checkBox1.Text = "Item" + i.ToString(); i++;
            G7checkBox2.Text = "Item" + i.ToString(); i++;
            G7checkBox3.Text = "Item" + i.ToString(); i++;
            G7checkBox4.Text = "Item" + i.ToString(); i++;
            G7checkBox5.Text = "Item" + i.ToString(); i++;
            G7checkBox6.Text = "Item" + i.ToString(); i++;
            G7checkBox7.Text = "Item" + i.ToString(); i++;
            G7checkBox8.Text = "Item" + i.ToString(); i++;
            i = 1;
            G8checkBox1.Text = "Item" + i.ToString(); i++;
            G8checkBox2.Text = "Item" + i.ToString(); i++;
            G8checkBox3.Text = "Item" + i.ToString(); i++;
            G8checkBox4.Text = "Item" + i.ToString(); i++;
            G8checkBox5.Text = "Item" + i.ToString(); i++;
            G8checkBox6.Text = "Item" + i.ToString(); i++;
            G8checkBox7.Text = "Item" + i.ToString(); i++;
            G8checkBox8.Text = "Item" + i.ToString(); i++;
        }


        #endregion
        #region //设置checkBox的文本属性，选中属性
        private void SetCheckBoxText(int GroupNum,int Index,string text)
        {
            switch (GroupNum)
            { 
                case 1:
                    switch (Index)
                    {
                        case 1: G1checkBox1.Text = text;
                            break;
                        case 2: G1checkBox2.Text = text;
                            break;
                        case 3: G1checkBox3.Text = text;
                            break;
                        case 4: G1checkBox4.Text = text;
                            break;
                        case 5: G1checkBox5.Text = text;
                            break;
                        case 6: G1checkBox6.Text = text;
                            break;
                        case 7: G1checkBox7.Text = text;
                            break;
                        case 8: G1checkBox8.Text = text;
                            break;
                    }
                    break;
                case 2:
                    switch (Index)
                    {
                        case 1: G2checkBox1.Text = text;
                            break;
                        case 2: G2checkBox2.Text = text;
                            break;
                        case 3: G2checkBox3.Text = text;
                            break;
                        case 4: G2checkBox4.Text = text;
                            break;
                        case 5: G2checkBox5.Text = text;
                            break;
                        case 6: G2checkBox6.Text = text;
                            break;
                        case 7: G2checkBox7.Text = text;
                            break;
                        case 8: G2checkBox8.Text = text;
                            break;
                    }
                    break;
                case 3:
                    switch (Index)
                    {
                        case 1: G3checkBox1.Text = text;
                            break;
                        case 2: G3checkBox2.Text = text;
                            break;
                        case 3: G3checkBox3.Text = text;
                            break;
                        case 4: G3checkBox4.Text = text;
                            break;
                        case 5: G3checkBox5.Text = text;
                            break;
                        case 6: G3checkBox6.Text = text;
                            break;
                        case 7: G3checkBox7.Text = text;
                            break;
                        case 8: G3checkBox8.Text = text;
                            break;
                    }
                    break;
                case 4:
                    switch (Index)
                    {
                        case 1: G4checkBox1.Text = text;
                            break;
                        case 2: G4checkBox2.Text = text;
                            break;
                        case 3: G4checkBox3.Text = text;
                            break;
                        case 4: G4checkBox4.Text = text;
                            break;
                        case 5: G4checkBox5.Text = text;
                            break;
                        case 6: G4checkBox6.Text = text;
                            break;
                        case 7: G4checkBox7.Text = text;
                            break;
                        case 8: G4checkBox8.Text = text;
                            break;
                    }
                    break;
                case 5:
                    switch (Index)
                    {
                        case 1: G5checkBox1.Text = text;
                            break;
                        case 2: G5checkBox2.Text = text;
                            break;
                        case 3: G5checkBox3.Text = text;
                            break;
                        case 4: G5checkBox4.Text = text;
                            break;
                        case 5: G5checkBox5.Text = text;
                            break;
                        case 6: G5checkBox6.Text = text;
                            break;
                        case 7: G5checkBox7.Text = text;
                            break;
                        case 8: G5checkBox8.Text = text;
                            break;
                    }
                    break;
                case 6:
                    switch (Index)
                    {
                        case 1: G6checkBox1.Text = text;
                            break;
                        case 2: G6checkBox2.Text = text;
                            break;
                        case 3: G6checkBox3.Text = text;
                            break;
                        case 4: G6checkBox4.Text = text;
                            break;
                        case 5: G6checkBox5.Text = text;
                            break;
                        case 6: G6checkBox6.Text = text;
                            break;
                        case 7: G6checkBox7.Text = text;
                            break;
                        case 8: G6checkBox8.Text = text;
                            break;
                    }
                    break;
                case 7:
                    switch (Index)
                    {
                        case 1: G7checkBox1.Text = text;
                            break;
                        case 2: G7checkBox2.Text = text;
                            break;
                        case 3: G7checkBox3.Text = text;
                            break;
                        case 4: G7checkBox4.Text = text;
                            break;
                        case 5: G7checkBox5.Text = text;
                            break;
                        case 6: G7checkBox6.Text = text;
                            break;
                        case 7: G7checkBox7.Text = text;
                            break;
                        case 8: G7checkBox8.Text = text;
                            break;
                    }
                    break;
                case 8:
                    switch (Index)
                    {
                        case 1: G8checkBox1.Text = text;
                            break;
                        case 2: G8checkBox2.Text = text;
                            break;
                        case 3: G8checkBox3.Text = text;
                            break;
                        case 4: G8checkBox4.Text = text;
                            break;
                        case 5: G8checkBox5.Text = text;
                            break;
                        case 6: G8checkBox6.Text = text;
                            break;
                        case 7: G8checkBox7.Text = text;
                            break;
                        case 8: G8checkBox8.Text = text;
                            break;
                    }
                    break;
            }
        }
        /// <summary>
        /// 设置打勾或取消（组1--8,索引1---8）
        /// </summary>
        /// <param name="GroupNum"></param>
        /// <param name="Index"></param>
        /// <param name="flag"></param>
        private void SetCheckBoxFlag(int GroupNum, int Index, bool flag)
        {
            Color trueColor = Color.Red;
            Color falseColor = Color.Green;
            switch (GroupNum)
            {
                case 1:
                    switch (Index)
                    {
                        case 1: G1checkBox1.Checked = flag;
                            if (flag == true) G1checkBox1.ForeColor = trueColor;
                            else G1checkBox1.ForeColor = falseColor;
                            break;
                        case 2: G1checkBox2.Checked = flag;
                            if (flag == true) G1checkBox2.ForeColor = trueColor;
                            else G1checkBox2.ForeColor = falseColor;
                            break;
                        case 3: G1checkBox3.Checked = flag;
                            if (flag == true) G1checkBox3.ForeColor = trueColor;
                            else G1checkBox3.ForeColor = falseColor;
                            break;
                        case 4: G1checkBox4.Checked = flag;
                            if (flag == true) G1checkBox4.ForeColor = trueColor;
                            else G1checkBox4.ForeColor = falseColor;
                            break;
                        case 5: G1checkBox5.Checked = flag;
                            if (flag == true) G1checkBox5.ForeColor = trueColor;
                            else G1checkBox5.ForeColor = falseColor;
                            break;
                        case 6: G1checkBox6.Checked = flag;
                            if (flag == true) G1checkBox6.ForeColor = trueColor;
                            else G1checkBox6.ForeColor = falseColor;
                            break;
                        case 7: G1checkBox7.Checked = flag;
                            if (flag == true) G1checkBox7.ForeColor = trueColor;
                            else G1checkBox7.ForeColor = falseColor;
                            break;
                        case 8: G1checkBox8.Checked = flag;
                            if (flag == true) G1checkBox8.ForeColor = trueColor;
                            else G1checkBox8.ForeColor = falseColor;
                            break;
                    }
                    break;
                case 2:
                    switch (Index)
                    {
                        case 1: G2checkBox1.Checked = flag;
                            if (flag == true) G2checkBox1.ForeColor = trueColor;
                            else G2checkBox1.ForeColor = falseColor;
                            break;
                        case 2: G2checkBox2.Checked = flag;
                            if (flag == true) G2checkBox2.ForeColor = trueColor;
                            else G2checkBox2.ForeColor = falseColor;
                            break;
                        case 3: G2checkBox3.Checked = flag;
                            if (flag == true) G2checkBox3.ForeColor = trueColor;
                            else G2checkBox3.ForeColor = falseColor;
                            break;
                        case 4: G2checkBox4.Checked = flag;
                            if (flag == true) G2checkBox4.ForeColor = trueColor;
                            else G2checkBox4.ForeColor = falseColor;
                            break;
                        case 5: G2checkBox5.Checked = flag;
                            if (flag == true) G2checkBox5.ForeColor = trueColor;
                            else G2checkBox5.ForeColor = falseColor;
                            break;
                        case 6: G2checkBox6.Checked = flag;
                            if (flag == true) G2checkBox6.ForeColor = trueColor;
                            else G2checkBox6.ForeColor = falseColor;
                            break;
                        case 7: G2checkBox7.Checked = flag;
                            if (flag == true) G2checkBox7.ForeColor = trueColor;
                            else G2checkBox7.ForeColor = falseColor;
                            break;
                        case 8: G2checkBox8.Checked = flag;
                            if (flag == true) G2checkBox8.ForeColor = trueColor;
                            else G2checkBox8.ForeColor = falseColor;
                            break;
                    }
                    break;
                case 3:
                    switch (Index)
                    {
                        case 1: G3checkBox1.Checked = flag;
                            if (flag == true) G3checkBox1.ForeColor = trueColor;
                            else G3checkBox1.ForeColor = falseColor;
                            break;
                        case 2: G3checkBox2.Checked = flag;
                            if (flag == true) G3checkBox2.ForeColor = trueColor;
                            else G3checkBox2.ForeColor = falseColor;
                            break;
                        case 3: G3checkBox3.Checked = flag;
                            if (flag == true) G3checkBox3.ForeColor = trueColor;
                            else G3checkBox3.ForeColor = falseColor;
                            break;
                        case 4: G3checkBox4.Checked = flag;
                            if (flag == true) G3checkBox4.ForeColor = trueColor;
                            else G3checkBox4.ForeColor = falseColor;
                            break;
                        case 5: G3checkBox5.Checked = flag;
                            if (flag == true) G3checkBox5.ForeColor = trueColor;
                            else G3checkBox5.ForeColor = falseColor;
                            break;
                        case 6: G3checkBox6.Checked = flag;
                            if (flag == true) G3checkBox6.ForeColor = trueColor;
                            else G3checkBox6.ForeColor = falseColor;
                            break;
                        case 7: G3checkBox7.Checked = flag;
                            if (flag == true) G3checkBox7.ForeColor = trueColor;
                            else G3checkBox7.ForeColor = falseColor;
                            break;
                        case 8: G3checkBox8.Checked = flag;
                            if (flag == true) G3checkBox8.ForeColor = trueColor;
                            else G3checkBox8.ForeColor = falseColor;
                            break;
                    }
                    break;
                case 4:
                    switch (Index)
                    {
                        case 1: G4checkBox1.Checked = flag;
                            if (flag == true) G4checkBox1.ForeColor = trueColor;
                            else G4checkBox1.ForeColor = falseColor;
                            break;
                        case 2: G4checkBox2.Checked = flag;
                            if (flag == true) G4checkBox2.ForeColor = trueColor;
                            else G4checkBox2.ForeColor = falseColor;
                            break;
                        case 3: G4checkBox3.Checked = flag;
                            if (flag == true) G4checkBox3.ForeColor = trueColor;
                            else G4checkBox3.ForeColor = falseColor;
                            break;
                        case 4: G4checkBox4.Checked = flag;
                            if (flag == true) G4checkBox4.ForeColor = trueColor;
                            else G4checkBox4.ForeColor = falseColor;
                            break;
                        case 5: G4checkBox5.Checked = flag;
                            if (flag == true) G4checkBox5.ForeColor = trueColor;
                            else G4checkBox5.ForeColor = falseColor;
                            break;
                        case 6: G4checkBox6.Checked = flag;
                            if (flag == true) G4checkBox6.ForeColor = trueColor;
                            else G4checkBox6.ForeColor = falseColor;
                            break;
                        case 7: G4checkBox7.Checked = flag;
                            if (flag == true) G4checkBox7.ForeColor = trueColor;
                            else G4checkBox7.ForeColor = falseColor;
                            break;
                        case 8: G4checkBox8.Checked = flag;
                            if (flag == true) G4checkBox8.ForeColor = trueColor;
                            else G4checkBox8.ForeColor = falseColor;
                            break;
                    }
                    break;
                case 5:
                    switch (Index)
                    {
                        case 1: G5checkBox1.Checked = flag;
                            if (flag == true) G5checkBox1.ForeColor = trueColor;
                            else G5checkBox1.ForeColor = falseColor;
                            break;
                        case 2: G5checkBox2.Checked = flag;
                            if (flag == true) G5checkBox2.ForeColor = trueColor;
                            else G5checkBox2.ForeColor = falseColor;
                            break;
                        case 3: G5checkBox3.Checked = flag;
                            if (flag == true) G5checkBox3.ForeColor = trueColor;
                            else G5checkBox3.ForeColor = falseColor;
                            break;
                        case 4: G5checkBox4.Checked = flag;
                            if (flag == true) G5checkBox4.ForeColor = trueColor;
                            else G5checkBox4.ForeColor = falseColor;
                            break;
                        case 5: G5checkBox5.Checked = flag;
                            if (flag == true) G5checkBox5.ForeColor = trueColor;
                            else G5checkBox5.ForeColor = falseColor;
                            break;
                        case 6: G5checkBox6.Checked = flag;
                            if (flag == true) G5checkBox6.ForeColor = trueColor;
                            else G5checkBox6.ForeColor = falseColor;
                            break;
                        case 7: G5checkBox7.Checked = flag;
                            if (flag == true) G5checkBox7.ForeColor = trueColor;
                            else G5checkBox7.ForeColor = falseColor;
                            break;
                        case 8: G5checkBox8.Checked = flag;
                            if (flag == true) G5checkBox8.ForeColor = trueColor;
                            else G5checkBox8.ForeColor = falseColor;
                            break;
                    }
                    break;
                case 6:
                    switch (Index)
                    {
                        case 1: G6checkBox1.Checked = flag;
                            if (flag == true) G6checkBox1.ForeColor = trueColor;
                            else G6checkBox1.ForeColor = falseColor;
                            break;
                        case 2: G6checkBox2.Checked = flag;
                            if (flag == true) G6checkBox2.ForeColor = trueColor;
                            else G6checkBox2.ForeColor = falseColor;
                            break;
                        case 3: G6checkBox3.Checked = flag;
                            if (flag == true) G6checkBox3.ForeColor = trueColor;
                            else G6checkBox3.ForeColor = falseColor;
                            break;
                        case 4: G6checkBox4.Checked = flag;
                            if (flag == true) G6checkBox4.ForeColor = trueColor;
                            else G6checkBox4.ForeColor = falseColor;
                            break;
                        case 5: G6checkBox5.Checked = flag;
                            if (flag == true) G6checkBox5.ForeColor = trueColor;
                            else G6checkBox5.ForeColor = falseColor;
                            break;
                        case 6: G6checkBox6.Checked = flag;
                            if (flag == true) G6checkBox6.ForeColor = trueColor;
                            else G6checkBox6.ForeColor = falseColor;
                            break;
                        case 7: G6checkBox7.Checked = flag;
                            if (flag == true) G6checkBox7.ForeColor = trueColor;
                            else G6checkBox7.ForeColor = falseColor;
                            break;
                        case 8: G6checkBox8.Checked = flag;
                            if (flag == true) G6checkBox8.ForeColor = trueColor;
                            else G6checkBox8.ForeColor = falseColor;
                            break;
                    }
                    break;
                case 7:
                    switch (Index)
                    {
                        case 1: G7checkBox1.Checked = flag;
                            if (flag == true) G7checkBox1.ForeColor = trueColor;
                            else G7checkBox1.ForeColor = falseColor;
                            break;
                        case 2: G7checkBox2.Checked = flag;
                            if (flag == true) G7checkBox2.ForeColor = trueColor;
                            else G7checkBox2.ForeColor = falseColor;
                            break;
                        case 3: G7checkBox3.Checked = flag;
                            if (flag == true) G7checkBox3.ForeColor = trueColor;
                            else G7checkBox3.ForeColor = falseColor;
                            break;
                        case 4: G7checkBox4.Checked = flag;
                            if (flag == true) G7checkBox4.ForeColor = trueColor;
                            else G7checkBox4.ForeColor = falseColor;
                            break;
                        case 5: G7checkBox5.Checked = flag;
                            if (flag == true) G7checkBox5.ForeColor = trueColor;
                            else G7checkBox5.ForeColor = falseColor;
                            break;
                        case 6: G7checkBox6.Checked = flag;
                            if (flag == true) G7checkBox6.ForeColor = trueColor;
                            else G7checkBox6.ForeColor = falseColor;
                            break;
                        case 7: G7checkBox7.Checked = flag;
                            if (flag == true) G7checkBox7.ForeColor = trueColor;
                            else G7checkBox7.ForeColor = falseColor;
                            break;
                        case 8: G7checkBox8.Checked = flag;
                            if (flag == true) G7checkBox8.ForeColor = trueColor;
                            else G7checkBox8.ForeColor = falseColor;
                            break;
                    }
                    break;
                case 8:
                    switch (Index)
                    {
                        case 1: G8checkBox1.Checked = flag;
                            if (flag == true) G8checkBox1.ForeColor = trueColor;
                            else G8checkBox1.ForeColor = falseColor;
                            break;
                        case 2: G8checkBox2.Checked = flag;
                            if (flag == true) G8checkBox2.ForeColor = trueColor;
                            else G8checkBox2.ForeColor = falseColor;
                            break;
                        case 3: G8checkBox3.Checked = flag;
                            if (flag == true) G8checkBox3.ForeColor = trueColor;
                            else G8checkBox3.ForeColor = falseColor;
                            break;
                        case 4: G8checkBox4.Checked = flag;
                            if (flag == true) G8checkBox4.ForeColor = trueColor;
                            else G8checkBox4.ForeColor = falseColor;
                            break;
                        case 5: G8checkBox5.Checked = flag;
                            if (flag == true) G8checkBox5.ForeColor = trueColor;
                            else G8checkBox5.ForeColor = falseColor;
                            break;
                        case 6: G8checkBox6.Checked = flag;
                            if (flag == true) G8checkBox6.ForeColor = trueColor;
                            else G8checkBox6.ForeColor = falseColor;
                            break;
                        case 7: G8checkBox7.Checked = flag;
                            if (flag == true) G8checkBox7.ForeColor = trueColor;
                            else G8checkBox7.ForeColor = falseColor;
                            break;
                        case 8: G8checkBox8.Checked = flag;
                            if (flag == true) G8checkBox8.ForeColor = trueColor;
                            else G8checkBox8.ForeColor = falseColor;
                            break;
                    }
                    break;
            }
        }

        #endregion
        #region //解码数据显示到check box
        //最多解码8个自己，字节按照先后顺序排1---8，对应checkbox 1组到8组，每个字节对应一组，每个位对应一个checkbox，位=1，checkbox打勾，位=0，checkbox不打勾
        //每个组高位在上面，地位在下面，与字节的高低位对应。
        private void DecodeDataToCheckBox(byte[] para, byte length)
        {
            if (length > 8) length = 8;
            bool flag = false;
            for (byte GroupNum = 0; GroupNum < length; GroupNum++)
            {
                byte temp = para[GroupNum];
                for (byte Index = 0; Index < 8; Index++)
                {
                    if ((temp & 0x01) == 0x01) flag = true;
                    else flag = false;
                    temp = (byte)(temp >> 1);
                    DispGroupStatus(GroupNum + 1, Index + 1, flag);
                }
            }
        }
        #endregion
        #region //字典处理
        private void InitDictionaryIO(int itemAmout)
        {
            int i;
            DictionaryIO.Clear();
            for (i = 0; i < itemAmout; i++)
            {
                DictionaryIO.Add(i, "NONE"+i.ToString());
            }
            if (ConsoleWindowOpenFlag == true)
            {
                Console.WriteLine("InitDictionaryIO");
            }
        }

        private void RenewDictionaryKeyToUI()
        {
            Dictionary<int, string>.ValueCollection ValCol = DictionaryIO.Values;
            int group=1;
            int index=1;
            if (ConsoleWindowOpenFlag == true)
            {
                Console.WriteLine("ValCol=" + ValCol.Count);
            }
            foreach (string Val in ValCol)
            {
                SetCheckBoxText(group, index++, Val);
                if (index >= 9)
                {
                    group++;
                    index = 1;
                }
            }
        }
        #endregion
        #region // 打开配置文件
        private string GetCfgFilePath()
        {
            string filePath = "";
            OpenFileDialog fileDialog = new OpenFileDialog();
            //fileDialog.FileName = "";
            //fileDialog.DefaultExt = "*.*";
            //fileDialog.Filter = "全部文件(.*)|*.*";
            //fileDialog.InitialDirectory = Application.StartupPath;//设置打开控件后，默认目录为exe运行文件所在的文件夹
            //fileDialog.Filter = "All files (*.*)|*.*|txt files (*.txt)|*.txt";//设置打开的文件类型
            fileDialog.Filter = "Txt files (*.txt)|*.txt|Config files (*.ini)|*.ini";//设置打开的文件类型
            fileDialog.RestoreDirectory = true;//设置对话框是否记忆之前打开的目录
            if (DialogResult.OK == fileDialog.ShowDialog())
            {
                filePath = fileDialog.FileName;
            }
            return filePath;
        }

        private string[] SplitCfgFileLine(string lineText)
        {
            string[] temp = lineText.Split(new char[] { ' ', '=', ',', '.' });
            return temp;
        }

        string ConfigDir = "Config";//
        private void RenewCfgFileList()
        {
            DirectoryInfo Dir = new DirectoryInfo(ConfigDir);
            if (Dir.Exists)
            {
                FileInfo[] fileArr = Dir.GetFiles();
                if (fileArr.Length > 0)
                {
                    comboBoxCfgFileList.Items.Clear();
                    foreach (FileInfo file in fileArr)
                    {
                        comboBoxCfgFileList.Items.Add(file);
                    }
                    comboBoxCfgFileList.SelectedIndex = 0;
                }
            }
        }

        public void DecodeCfgFile(string fileName)
        {
            string FilePath = System.Environment.CurrentDirectory;
            FilePath += "\\Config\\" + fileName;
            if (File.Exists(FilePath))
            {
                if (FilePath.Contains(".ini"))
                {
                    string[] lineText = File.ReadAllLines(FilePath);
                    DictionaryIO.Clear();
                    for (int i = 0; i < lineText.Length; i++)
                    {
                        string temp = lineText[i];
                        if (temp.Contains("{")) temp = temp.Replace("{", " ");
                        if (temp.Contains("}")) temp = temp.Replace("}", " ");
                        temp = temp.Trim();
                        if (temp.Trim() != "")
                        {
                            string[] lineMember = SplitCfgFileLine(temp);
                            if (lineMember.Length >= 2)
                            {
                                int Key = Convert.ToInt32(lineMember[0]);
                                string Val = lineMember[1];
                                DictionaryIO.Add(Key, Val);
                            }
                        }
                    }
                }
            }
        }
        #endregion
        #region // 打开文件
        private void SaveLogToFile()
        {
            string filePath = "";
            SaveFileDialog fileDialog = new SaveFileDialog();
            //fileDialog.FileName = "";
            //fileDialog.DefaultExt = "*.*";
            //fileDialog.Filter = "全部文件(.*)|*.*";
            //fileDialog.InitialDirectory = Application.StartupPath;//设置打开控件后，默认目录为exe运行文件所在的文件夹
            //fileDialog.Filter = "All files (*.*)|*.*|txt files (*.txt)|*.txt";//设置打开的文件类型
            fileDialog.Filter = "Txt files (*.txt)|*.txt|Config files (*.ini)|*.ini";//设置打开的文件类型
            fileDialog.RestoreDirectory = true;//设置对话框是否记忆之前打开的目录
            if (DialogResult.OK == fileDialog.ShowDialog())
            {
                filePath = fileDialog.FileName;
            }
            
        }
        #endregion
        #region // 自定义功能 获取串口列表
        private void DispComNameList()
        {
            string[] temp = comY1.GetComNameList();
            comboBoxComName.Items.Clear();
            if (temp.Length > 0)
            {
                for (int i = 0; i < temp.Length; i++)
                {
                    comboBoxComName.Items.Add(temp[i]);
                }
                //comboBoxComName.SelectedIndex = 1;
                comboBoxComName.SelectedIndex = temp.Length - 1;
            }
            else
            {
                comboBoxComName.Items.Add("本机无串口");
                comboBoxComName.SelectedIndex = 0;
            }
        }

        #endregion
        #region ///CRC函数
        // --------------------------------------------------------------
        //      CRC16计算方法：使用2个256长度的校验表

        //		CRC-16/MODBUS       x16+x15+x2+1
        // --------------------------------------------------------------
        //////////////*高位表*///////////////////

        byte[] auchCRCHi = new byte[] {
                0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
                0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
                0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
                0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
                0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
                0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
                0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
                0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
                0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
                0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
                0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
                0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
                0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
                0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
                0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
                0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
                0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
                0x40
                };

        //////////////*低位表*///////////////////
        byte[] auchCRCLo = new byte[] {
                0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
                0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
                0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
                0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
                0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
                0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
                0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
                0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
                0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
                0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
                0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
                0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
                0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
                0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
                0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
                0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
                0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
                0x40
                };
        /******************************************************************************
        * 函数名   : CRC16
        * 描述     : 16位CRC校验函数，查表法
        * 输入     : 
                 *puchMsg:	求16位CRC校验数据地址
                 usDataLen：校验数据个数
        * 输出     : None
        * 返回值   : 16位CRC校验值，高位在前，低位在后
        ******************************************************************************/
        UInt16 GetCrc16(byte[] DataArray, UInt16 usDataLen)
        {
            UInt16 i = 0;
            UInt16 crcVal = 0;
            byte uchCRCHi = 0xFF; 	//高CRC字节初始化		
            byte uchCRCLo = 0xFF; 	//低CRC字节初始化		
            UInt16 uIndex; 		// CRC循环中的索引			
            while (usDataLen > 0)
            {
                usDataLen--;
                uIndex = (UInt16)(uchCRCLo ^ DataArray[i++]);
                uchCRCLo = (byte)(uchCRCHi ^ auchCRCHi[uIndex]);
                uchCRCHi = auchCRCLo[uIndex];
            }
            crcVal = (UInt16)(uchCRCHi << 8);
            crcVal = (UInt16)(crcVal + (UInt16)uchCRCLo);
            return crcVal;
        }
        #endregion
        #region ///串口常用命令函数
        //{0xB4, 0x10, 0x01, 0x0A      0x01, 0xF1,        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x55,  0x66, 0x4B};
        //帧头， 帧长,帧序号,参数长度 命令，命令反码，  数据1   ...    ...    ...      ...          数据N，校验H,校验L,帧尾（每段一个字节）
        
        private void ComTx0Byte(byte cmdLineNum,byte cmd)
        {
            byte[] temp = new byte[] { ProFrameHead, 2, 3, 4, 5, 6,7,8, ProFrameEnd };
            temp[1] = 9;
            temp[2] = cmdLineNum;
            temp[3] = 2;                    //参数长度
            temp[4] = cmd;
            temp[5] = (byte)~cmd;
            UInt16 CrcVal = GetCrc16(temp, 6);
            temp[6] = (byte)(CrcVal / 256);
            temp[7] = (byte)(CrcVal % 256);
            comY1.SendHex(true, temp, 0, temp.Length);
        }

        private void ComTx1Byte(byte cmdLineNum,byte cmd, byte data)
        {
            byte[] temp = new byte[] { ProFrameHead, 2, 3, 4, 5, 6, 7,8,9, ProFrameEnd };
            temp[1] = 10;
            temp[2] = cmdLineNum;
            temp[3] = 3;                    //参数长度      //参数长度包含命令及其反码
            temp[4] = cmd;
            temp[5] = (byte)~cmd;
            temp[6] = data;
            UInt16 CrcVal = GetCrc16(temp, 7);
            temp[7] = (byte)(CrcVal / 256);
            temp[8] = (byte)(CrcVal % 256);
            comY1.SendHex(true, temp, 0, temp.Length);
        }

        private void ComTx1U16(byte cmdLineNum,byte cmd ,UInt16 data)
        {
            byte[] temp = new byte[] { ProFrameHead, 2, 3, 4, 5, 6, 7,8,9,10, ProFrameEnd };
            temp[1] = 11;
            temp[2] = cmdLineNum;
            temp[3] = 3;                    //参数长度      //参数长度包含命令及其反码
            temp[4] = cmd;
            temp[5] = (byte)~cmd;
            temp[6] = (byte)(data / 256);
            temp[7] = (byte)(data % 256);
            UInt16 CrcVal = GetCrc16(temp, 8);
            temp[8] = (byte)(CrcVal / 256);
            temp[9] = (byte)(CrcVal % 256);
            comY1.SendHex(true, temp, 0, temp.Length);
        }
        /// <summary>
        /// SimulateFlag=真时生成仿真数据（直接将串口数据填充到接收队列中）
        /// </summary>
        /// <param name="cmdLineNum"></param>
        /// <param name="cmd"></param>
        /// <param name="data"></param>
        /// <param name="length"></param>
        /// <param name="SimulateFlag"></param>
        private void ComTxNU8(byte cmdLineNum, byte cmd, byte[] data ,byte length,bool SimulateFlag)
        {
            string TxString="";
            byte index = 6;
            byte[] temp = new byte[length+9];// { ProFrameHead, 2, 3, 4, 5, 6, 7, 8, 9, ProFrameEnd };
            temp[0] = ProFrameHead;
            temp[1] = (byte)(length + 9);
            temp[2] = cmdLineNum;
            temp[3] = (byte)(length + 2);                    //参数长度  //参数长度包含命令及其反码
            temp[4] = cmd;
            temp[5] = (byte)~cmd;
            //temp[5] = 0x05;
            for (int i = 0; i < length; i++)
            {
                temp[index++] = data[i];
            }
            UInt16 CrcVal = GetCrc16(temp, index);
            temp[index++] = (byte)(CrcVal / 256);
            temp[index++] = (byte)(CrcVal % 256);
            temp[index++] = ProFrameEnd;
            if (SimulateFlag == true)
            {
                for (int i = 0; i < temp.Length; i++)
                {
                    ComRxDataQueue.Enqueue(temp[i]);
                    TxString += temp[i].ToString("X2")+" ";
                }
            }
            else
            {
                comY1.SendHex(true, temp, 0, temp.Length);
            }

            textBoxTestPara.Text = TxString;
        }

        #endregion
        #region //委托
        private delegate void dispConnectedImage(bool ConnectOK);           //代理

        private void DispConnectedImage(bool ConnectOK)
        {
            //if (this.InvokeRequired)
            if (this.pictureBoxConnectStatus.InvokeRequired)
            {
                dispConnectedImage dispConImage = new dispConnectedImage(DispConnectedImage);
                this.Invoke(dispConImage, new object[] { ConnectOK });
            }
            else
            {
                string path = "";
                if (ConnectOK == true)
                    path = Application.StartupPath + @"\PIC\ConOk4.png";
                else
                    path = Application.StartupPath + @"\PIC\ConFail4.png";
                if (File.Exists(path))
                    pictureBoxConnectStatus.Image = Image.FromFile(path);
            }
        }
        /// 打勾或取消（组1--8,索引1---8）
        private delegate void dispGroupStatus(int GroupNum, int Index, bool flag);
        /// 打勾或取消（组1--8,索引1---8）
        private void DispGroupStatus(int GroupNum, int Index, bool flag)
        {
            if(this.InvokeRequired)
            {
                dispGroupStatus d = new dispGroupStatus(DispGroupStatus);
                this.Invoke(d, new object[] { GroupNum,  Index,  flag });
            }
            else
            {
                SetCheckBoxFlag(GroupNum, Index, flag);
            }
        }



        private void LogAddMessage(bool InsteadLastLine, bool addTimeFlag, string message)
        {
            string temp = "";
            temp = DateTime.Now.ToString("HH:mm:ss");
            if (addTimeFlag==true)
                temp += " " + message;
            else
                temp =  message;
            bool scroll = false;
            if (listBoxReceiceLog.TopIndex == listBoxReceiceLog.Items.Count - (int)(listBoxReceiceLog.Height / listBoxReceiceLog.ItemHeight)) scroll = true;

            if (InsteadLastLine == true)
            {
                if (listBoxReceiceLog.Items.Count > 1)
                {
                    listBoxReceiceLog.Items.RemoveAt(listBoxReceiceLog.Items.Count - 1);
                    listBoxReceiceLog.Items.Add(temp);
                }
            }
            else
                listBoxReceiceLog.Items.Add(temp);
            if (scroll) listBoxReceiceLog.TopIndex = listBoxReceiceLog.Items.Count - (int)(listBoxReceiceLog.Height / listBoxReceiceLog.ItemHeight);

        }


        private delegate void listBoxReceiceLogAddLine(bool InsteadLastLine, bool addTimeFlag, string Message);         //代理


        private void ListBoxLogAddMesssage(bool InsteadLastLine, bool addTimeFlag, string message)
        {
            if (this.listBoxReceiceLog.InvokeRequired)
            {
                listBoxReceiceLogAddLine listboxLog = new listBoxReceiceLogAddLine(ListBoxLogAddMesssage);
                this.Invoke(listboxLog, new object[] { InsteadLastLine, addTimeFlag, message });
            }
            else
            {
                LogAddMessage(InsteadLastLine, addTimeFlag, message);
            }
        }

        #endregion
        #region ///线程启动
        /// <summary>
        /// 所有线程启动的地方
        /// </summary>
        private void ThreadsStart()
        {
            //接收数据线程
            Thread ThreadIapReceiveComData = new Thread(new ThreadStart(IapReceiveComDataThread));
            ThreadIapReceiveComData.IsBackground = true;
            ThreadIapReceiveComData.Name = "IapReceiveComDataThread";
            ThreadIapReceiveComData.Start();

            //协议解码线程
            Thread IapCmdDecodeThread = new Thread(new ThreadStart(IapRxProcessThread));
            IapCmdDecodeThread.IsBackground = true;
            IapCmdDecodeThread.Name = "IapRxProcessThread";
            IapCmdDecodeThread.Start();

            //
            Thread systemTimerhread = new Thread(new ThreadStart(SystemTimerThread));
            systemTimerhread.IsBackground = true;
            systemTimerhread.Name = "TestThread";
            systemTimerhread.Start();
            //测试线程
            Thread TestThread = new Thread(new ThreadStart(FuncTestThread));
            TestThread.IsBackground = true;
            TestThread.Name = "TestThread";
            TestThread.Start();

        }
        #endregion
        #region //串口解码线程
        /// <summary>
        /// 
        /// </summary>
        private void IapRxProcessThread()
        {
            byte data = 0, ProCmd = 0, ProInvCmd = 0, cmdLineNum = 0, ParaLength = 0; //数据,命令, 命令反码，命令行编号,参数长度（ 参数长度包含命令及其反码）
            byte CmdPara1 = 0, CmdPara2 = 0;
            //byte temp8A = 0, temp8B = 0, temp8C = 0;
            bool ProFrameStartFlag = false, GetNewFrameFlag = false;
            byte ProFrameLength = 100, ProFrameLengthBak = 0, ProFrameIndex = 0;
            byte[] ProFrameBuff = new byte[255];
            byte[] MonitorVarArray=new byte[8];
            //UInt16  temp16A = 0, temp16B = 0, temp16C = 0;
            UInt16 RxCheckSum = 0, CalCheckSum = 1;
            UInt32 SystemRunSenond = 0, temp32A;
            Thread.Sleep(1000);
            //{0xB4, 0x10, 0x01, 0x0A      0x01, 0xF1,        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x55,  0x66, 0x4B};
            //帧头， 帧长,帧序号,参数长度 命令，命令反码，  数据1   ...    ...    ...      ...          数据N，校验H,校验L,帧尾（每段一个字节）
            while (true)
            {
                #region //接收数据帧
                SystemRunSenond++;
                if (ComRxDataQueue.Count > 0)
                {
                    data = (byte)ComRxDataQueue.Dequeue();
                    if (data == ProFrameHead && ProFrameStartFlag == false)
                    {
                        ProFrameStartFlag = true;
                        ProFrameLength = 100; ProFrameLengthBak = 0; ProFrameIndex = 0;
                        ProFrameBuff[ProFrameIndex++] = data;
                    }
                    else if (ProFrameStartFlag == true)
                    {
                        if (ProFrameIndex == 1) ProFrameLength = data;
                        ProFrameBuff[ProFrameIndex++] = data;
                    }
                }
                else
                {
                    Thread.Sleep(100);
                }
                if (ProFrameLength == ProFrameIndex && data == ProFrameEnd)
                {
                    GetNewFrameFlag = true;
                    ProFrameStartFlag = false;
                    cmdLineNum = ProFrameBuff[2];
                    ParaLength = ProFrameBuff[3];
                    ProCmd = ProFrameBuff[4];
                    ProInvCmd = ProFrameBuff[5];
                    ProFrameLengthBak = ProFrameLength;
                    RxCheckSum = (UInt16)(ProFrameBuff[ProFrameIndex - 3] * 256 + ProFrameBuff[ProFrameIndex - 2]);
                    CalCheckSum = GetCrc16(ProFrameBuff, (UInt16)(ProFrameIndex - 3));
                    ProFrameLength = 100;
                    ProFrameIndex = 0;
                    //Console.WriteLine("ProCmd :" + ProCmd.ToString("X4"));
                    if (ProCmd != (byte)~ProInvCmd)
                    {
                        MessageBox.Show("命令正反码错误 正码=" + ProCmd.ToString("X2") + " 反码=" + ProInvCmd.ToString("X2"), "提示");
                        ProCmd = 0;
                        GetNewFrameFlag = false;
                        if (ConsoleWindowOpenFlag == true)
                            Console.WriteLine("cmdLineNum :" + cmdLineNum.ToString() + " ProCmd=" + ProCmd.ToString("X2") + " ProInvCmd=" + ProInvCmd.ToString("X2"));
                    }
                    //if (RxCheckSum != CalCheckSum)
                    //{
                    //    ProCmd = 0;
                    //    GetNewFrameFlag = false;
                    //    if (ConsoleWindowOpenFlag == true)
                    //        Console.WriteLine(" XXX RxCheckSum=0x" + RxCheckSum.ToString("X4") + " " + "CalCheckSum=0x" + CalCheckSum.ToString("X4") + " ");
                    //}
                    if (ConsoleWindowOpenFlag == true)
                    {
                        Console.WriteLine("cmdLineNum :" + cmdLineNum.ToString() + "ParaLength=" +ParaLength.ToString()+ " ProCmd=" + ProCmd.ToString("X2") + " ProInvCmd=" + ProInvCmd.ToString("X2"));
                    }
                }
                if (ProFrameIndex > ProFrameLength)
                {
                    GetNewFrameFlag = false;
                    ProFrameStartFlag = false;
                    ProCmd = 0;
                    ProFrameLength = 100;
                    ProFrameIndex = 0;
                }
                if (ProFrameIndex > 255)
                {
                    GetNewFrameFlag = false;
                    ProFrameStartFlag = false;
                    ProCmd = 0;
                    ProFrameLength = 100;
                    ProFrameIndex = 0;
                }
                #endregion

                if (GetNewFrameFlag == true)
                {
                    GetNewFrameFlag = false;
                    switch (ProCmd)
                    {
                        case PRO_CMD_CONNECT:
                            CmdPara1 = ProFrameBuff[6];
                            //ComY1Tx0Byte(PRO_CMD_FB_CONNECT);
                            if (ConsoleWindowOpenFlag == true) 
                            {
                                Console.WriteLine("PRO_CMD_CONNECT SystemRunSenond:" + SystemRunSenond.ToString() + " CmdPara1=" + CmdPara1);
                            }
                            break;
                        case PRO_CMD_FB_CONNECT:
                            DeviceConnectFlag = true;
                            DispConnectedImage(true);
                            if (ConsoleWindowOpenFlag == true) Console.WriteLine("PRO_CMD_FB_CONNECT BoardRunSenond:");
                            break;
                        case PRO_CMD_MONITOR_VAR_BIT:

                            for (int i = 0; i < ParaLength-2; i++)
                            {
                                MonitorVarArray[i] = ProFrameBuff[i + 6];
                                if (ConsoleWindowOpenFlag == true) Console.Write(" " + MonitorVarArray[i].ToString("X2"));
                            }
                            Console.WriteLine();Console.WriteLine("-------------------------------");
                            DecodeDataToCheckBox(MonitorVarArray, 8);
                            string message = logDataFormat + "[" + (ParaLength-2).ToString("X2")+ " ";       //参数长度包含命令及其反码
                            for (int i = 0; i < ParaLength - 2; i++) 
                            {
                                message += MonitorVarArray[i].ToString("X2") + " ";
                            }
                            message += "]";
                            ListBoxLogAddMesssage(false, listBoxLogAddTimeFlag, message);
                            break;
                    }
                }
            }
        }
        #endregion
        #region ///系统定时线程
        private void SystemTimerThread()
        {
            Thread.Sleep(1000);
            while (true)
            {
                Thread.Sleep(1000);                                     //每秒执行一次

            }
        }
        #endregion
        #region///测试线程
        private void FuncTestThread()
        {
            byte bTemp = 0;
            byte[] temp = new byte[] { 0x00, 0x81, 0x18, 0x11, 0x11, 0x11, 0x11, 0x11 };
            string message="";
            UInt16 cnt=1;
            int GroupNum=1;
            int Index=1;
            bool flag=true;
            Thread.Sleep(1000);

            while (true)
            {
                cnt++;
                if (ConsoleWindowOpenFlag == true)
                {
                    //Console.WriteLine("---FuncTestThread Running---" + cnt.ToString());
                }
                temp[0]=bTemp++;
                for (int i = 0; i < 8; i++)
                {
                    temp[i] = bTemp;
                }

                //DecodeDataToCheckBox(temp, 6);
                //message = "Data " ;
                //for (int i = 0; i < 8; i++) 
                //{ 
                //    message += temp[i].ToString("X2")+" ";
                //}
                //ListBoxLogAddMesssage(false, listBoxLogAddTimeFlag, message);

                Thread.Sleep(500);


                //DispGroupStatus(GroupNum, Index++, flag);
                //message = "test " + cnt.ToString();
                //ListBoxLogAddMesssage(false, listBoxLogAddTimeFlag, message);
                //if (Index >= 9)
                //{
                //    Index = 1;
                //    GroupNum++;
                //}

                //if (GroupNum >= 9)
                //{
                //    GroupNum = 1;
                //    if (flag == true)
                //        flag = false;
                //    else
                //        flag = true;
                //}



                //Thread.Sleep(100);


            }
        }
        #endregion
        #region //串口接收数据线程
        /// <summary>
        /// 串口数据接收线程---仅仅将数据接收--保存于接收缓存的队列中
        /// </summary>
        private void IapReceiveComDataThread()
        {
            //UInt32 SleepCnt1 = 0, SleepCnt2 = 0;
            byte[] RxByte = new byte[4096];
            int RxCount = 4096, i = 0;
            ComRxDataQueue.Clear();
            while (true)
            {
                if (comY1.IsGotNewData() == true)
                {
                    RxCount = comY1.GetRxByteCount();
                    comY1.GetHexArrayFromRxBuff(RxByte, ref RxCount);
                    for (i = 0; i < RxCount; i++)
                    {
                        ComRxDataQueue.Enqueue(RxByte[i]);
                    }
                }
                else
                {
                    Thread.Sleep(100);
                }
            }
        }
        #endregion
        #region //界面按钮操作

        private void SystemStartUI_EnableSet()
        {
            btnConnectDevice.Enabled = false;
            btnComClose.Enabled = false;
        }

        private void OpenCloseComUI_EnableSet(bool OpenFlag)
        {
            if (OpenFlag == true)
            {
                comboBoxComName.Enabled = false;
                comboBoxComBps.Enabled = false;
                btnRenewComNameList.Enabled = false;
                btnConnectDevice.Enabled = true;
                btnComOpen.Enabled = false;
                btnComClose.Enabled = true;
            }
            else
            {
                comboBoxComName.Enabled = true;
                comboBoxComBps.Enabled = true;
                btnRenewComNameList.Enabled = true;
                btnConnectDevice.Enabled = false;
                btnComOpen.Enabled = true;
                btnComClose.Enabled = false;
            }
        }


        private void btnRenewComNameList_Click(object sender, EventArgs e)
        {
            DispComNameList();
        }

        private void btnComOpen_Click(object sender, EventArgs e)
        {
            string Bsp = comboBoxComBps.Text.Trim();
            ComName = comboBoxComName.Text.Trim();
            if ("本机无串口" != ComName)
            {
                ComBps = Convert.ToInt32(Bsp);
                comY1.SetPortBaudRate(ComBps);
                comY1.SetPortName(ComName);
                comY1.Open();
                if (comY1.IsOpen == true)
                {
                    OpenCloseComUI_EnableSet(true);
                }
            }
            else
            {
                MessageBox.Show("本机无串口","提示");
            }
        }

        private void btnComClose_Click(object sender, EventArgs e)
        {
            if (comY1.IsOpen == true)
            {
                comY1.Close();
                btnComOpen.ForeColor = Color.Black;
                OpenCloseComUI_EnableSet(false);
                DispConnectedImage(false);
            }
        }

        private void btnConnectDevice_Click(object sender, EventArgs e)
        {
            ComTx1Byte(cmdLineNum,PRO_CMD_CONNECT, 0);
        }

        private void checkBoxLogAddDateTime_CheckedChanged(object sender, EventArgs e)
        {
            if(checkBoxLogAddDateTime.Checked==true)
            {
                checkBoxLogAddDateTime.ForeColor=Color.Red;
                listBoxLogAddTimeFlag = true;
            }
            else
            {
                checkBoxLogAddDateTime.ForeColor = Color.Green;
                listBoxLogAddTimeFlag = false;
            }
        }


        
        private void btnClearLog_Click(object sender, EventArgs e)
        {
            listBoxReceiceLog.Items.Clear();
            listBoxReceiceLog.Items.Add(" --------- 监控日志 --------- "); 
        }

        
        private void btnGenerateTestData_Click(object sender, EventArgs e)
        {
            byte[] data = new byte[8];
            //RenewDictionaryKeyToUI();
            //DecodeCfgFile();
            //RenewDictionaryKeyToUI();
            //ComTx1Byte(cmdLineNum++, PRO_CMD_CONNECT, 5);
            para++;
            for (int i = 0; i < 8; i++)
            {
                data[i] = para;
            }
            ComTxNU8(cmdLineNum++, PRO_CMD_MONITOR_VAR_BIT, data, 8,true);
        }
        
        private void btnSaveLog_Click(object sender, EventArgs e)
        {
            string path = "";
            if (listBoxReceiceLog.Items.Count >2)
            {
                SaveFileDialog sfile = new SaveFileDialog();
                //sfile.Filter = "Txt files (*.txt)|*.txt|log files (*.log)|*.log";//设置打开的文件类型
                sfile.Filter = "log文件|*.log|txt文件|*.txt";
                if (DialogResult.OK == sfile.ShowDialog())
                {
                    path = sfile.FileName;
                    //File.WriteAllLines(path, listBoxReceiceLog.Items);
                    StreamWriter sw = new StreamWriter(path,false); 
                    for(int i =0;i<listBoxReceiceLog.Items .Count ;i++)
                    {
                        sw.Write(listBoxReceiceLog.Items[i]) ;
                        sw.WriteLine ();

                    }
                    sw.Close();
                }
            }
        }

        private void btnOpenLogFile_Click(object sender, EventArgs e)
        {
            bool getLogFileFlag = false;
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.InitialDirectory = CurrentLogFilePath;
            openFileDialog.Filter = "log文件|*.log|txt文件|*.txt";
            openFileDialog.RestoreDirectory = true;
            openFileDialog.FilterIndex = 1;
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                string path=openFileDialog.FileName;
                string[] temp = File.ReadAllLines(path);
                for (int i = 0; i < temp.Length; i++)
                {
                    if (temp[i].Trim().Contains("监控日志") == true && getLogFileFlag == false)
                    {
                        listBoxReceiceLog.Items.Clear();
                        getLogFileFlag = true;
                        listBoxReceiceLog.Items.Add(temp[i].Trim());
                    }
                    else
                    {
                        listBoxReceiceLog.Items.Add(temp[i].Trim());
                    }
                }
            }
        }

        private void checkBoxOpenConsoleWindow_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxOpenConsoleWindow.Checked == true)
            {
                //AllocConsole();
                //ConsoleWindowOpenFlag = true;
                //Console.WriteLine("Open console window");
            }
            else
            {
                //ConsoleWindowOpenFlag = false;
                //FreeConsole();
            }
            MessageBox.Show("不支持此功能","提示");
        }

        private void listBoxReceiceLog_SelectedIndexChanged(object sender, EventArgs e)
        {
            string temp="";
            bool GetDataLengthFlag = false;
            byte DataLength = 0;
            byte[] MonitorVarArray=new byte[8];
            int index = listBoxReceiceLog.SelectedIndex;
            if(index>1)
                temp = listBoxReceiceLog.Items[index].ToString();
            if (ConsoleWindowOpenFlag == true)
            {
                Console.WriteLine("---select---" + temp);
            }
            if (temp.Contains(logDataFormat))
            {
                index = temp.IndexOf("[");
                string tt = temp.Remove(0,index+1);
                tt = tt.Replace("]","");
                string[] tempByte = tt.Split(new char[] { ',', ' ' });
                int j=0;
                for (int i = 0; i < tempByte.Length; i++)
                {
                    if (tempByte[i].Trim() != "")
                    {
                        if (GetDataLengthFlag == false)
                        {
                            DataLength = Convert.ToByte(tempByte[i].Trim(), 16);
                            GetDataLengthFlag = true;
                        }
                        else
                        {
                            if (j < DataLength)
                            {
                                MonitorVarArray[j++] = Convert.ToByte(tempByte[i].Trim(), 16);
                            }
                        }
                    }
                }
                DecodeDataToCheckBox(MonitorVarArray, 8);
                
            }
        }

        private void btnFrameFormatDisp_Click(object sender, EventArgs e)
        {
            string format = "";
            format = "帧头,帧长,帧序号,参数长度,命令,命令反码,数据1...数据N,校验H,校验L,帧尾\r\n";
            format += "帧长=全部数据长度，参数长度=命令正反吗+数据1...数据N\r\n";
            format += "本次版本不检测校验值，检测命令正负码\r\n";
            format += "帧定义：参考作者《嵌入式工程师 如何设计一个可靠的通信协议》\r\n";
            MessageBox.Show(format,"帧格式");
        }

        private void btnTestDownLine_Click(object sender, EventArgs e)
        {

            string temp=textBoxTestThisLine.Text.Trim();
            if (temp != "")
            {
                byte index=0;
                string[] items = temp.Split(new char[]{',',' '});
                byte[] btemp = new byte[items.Length];
                for (int i = 0; i < items.Length; i++)
                {
                    if (items[i].Trim() != "")
                    {
                        btemp[index++] = Convert.ToByte(items[i].Trim(),16);
                    }
                }
                for (int i = 0; i < index; i++)
                {
                    ComRxDataQueue.Enqueue(btemp[i]);
                }
            }
            else
            {
                MessageBox.Show("测试数据不能为空","提示");
            }
        }

        private void btnUpLineToDownLine_Click(object sender, EventArgs e)
        {
            textBoxTestThisLine.Text = textBoxTestPara.Text.Trim();
        }

        private void comboBoxCfgFileList_SelectedIndexChanged(object sender, EventArgs e)
        {
            string fileName=comboBoxCfgFileList.Text;
            if (fileName != "")
            {
                DecodeCfgFile(fileName);
                RenewDictionaryKeyToUI();
            }
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            Environment.Exit(0);
        }

        #endregion
    }
}
