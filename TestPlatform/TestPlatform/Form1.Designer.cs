namespace TestPlatform
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnAsciiToHEX = new System.Windows.Forms.Button();
            this.textBoxInputAscii = new System.Windows.Forms.TextBox();
            this.textBoxOutput = new System.Windows.Forms.TextBox();
            this.checkBoxInsertBlank = new System.Windows.Forms.CheckBox();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.progressBar2 = new System.Windows.Forms.ProgressBar();
            this.progressBar3 = new System.Windows.Forms.ProgressBar();
            this.checkBoxStart = new System.Windows.Forms.CheckBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // btnAsciiToHEX
            // 
            this.btnAsciiToHEX.Location = new System.Drawing.Point(336, 80);
            this.btnAsciiToHEX.Name = "btnAsciiToHEX";
            this.btnAsciiToHEX.Size = new System.Drawing.Size(144, 40);
            this.btnAsciiToHEX.TabIndex = 0;
            this.btnAsciiToHEX.Text = "字符转16进制数";
            this.btnAsciiToHEX.UseVisualStyleBackColor = true;
            this.btnAsciiToHEX.Click += new System.EventHandler(this.btnAsciiToHEX_Click);
            // 
            // textBoxInputAscii
            // 
            this.textBoxInputAscii.Location = new System.Drawing.Point(40, 32);
            this.textBoxInputAscii.Multiline = true;
            this.textBoxInputAscii.Name = "textBoxInputAscii";
            this.textBoxInputAscii.Size = new System.Drawing.Size(264, 88);
            this.textBoxInputAscii.TabIndex = 1;
            this.textBoxInputAscii.Text = "12345678ABCDEF";
            // 
            // textBoxOutput
            // 
            this.textBoxOutput.Location = new System.Drawing.Point(496, 32);
            this.textBoxOutput.Multiline = true;
            this.textBoxOutput.Name = "textBoxOutput";
            this.textBoxOutput.Size = new System.Drawing.Size(264, 96);
            this.textBoxOutput.TabIndex = 4;
            // 
            // checkBoxInsertBlank
            // 
            this.checkBoxInsertBlank.AutoSize = true;
            this.checkBoxInsertBlank.Location = new System.Drawing.Point(336, 48);
            this.checkBoxInsertBlank.Name = "checkBoxInsertBlank";
            this.checkBoxInsertBlank.Size = new System.Drawing.Size(89, 19);
            this.checkBoxInsertBlank.TabIndex = 5;
            this.checkBoxInsertBlank.Text = "插入空格";
            this.checkBoxInsertBlank.UseVisualStyleBackColor = true;
            this.checkBoxInsertBlank.CheckedChanged += new System.EventHandler(this.checkBoxInsertBlank_CheckedChanged);
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(64, 248);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(688, 23);
            this.progressBar1.TabIndex = 6;
            // 
            // progressBar2
            // 
            this.progressBar2.Location = new System.Drawing.Point(64, 304);
            this.progressBar2.Name = "progressBar2";
            this.progressBar2.Size = new System.Drawing.Size(688, 23);
            this.progressBar2.TabIndex = 7;
            // 
            // progressBar3
            // 
            this.progressBar3.Location = new System.Drawing.Point(64, 368);
            this.progressBar3.Name = "progressBar3";
            this.progressBar3.Size = new System.Drawing.Size(688, 23);
            this.progressBar3.TabIndex = 8;
            // 
            // checkBoxStart
            // 
            this.checkBoxStart.AutoSize = true;
            this.checkBoxStart.Location = new System.Drawing.Point(648, 200);
            this.checkBoxStart.Name = "checkBoxStart";
            this.checkBoxStart.Size = new System.Drawing.Size(59, 19);
            this.checkBoxStart.TabIndex = 9;
            this.checkBoxStart.Text = "开始";
            this.checkBoxStart.UseVisualStyleBackColor = true;
            this.checkBoxStart.CheckedChanged += new System.EventHandler(this.checkBoxStart_CheckedChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(64, 216);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(135, 15);
            this.label1.TabIndex = 10;
            this.label1.Text = "跨线程控制进度条1";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(64, 280);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(135, 15);
            this.label2.TabIndex = 11;
            this.label2.Text = "跨线程控制进度条2";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(64, 344);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(135, 15);
            this.label3.TabIndex = 12;
            this.label3.Text = "跨线程控制进度条3";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(801, 548);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.checkBoxStart);
            this.Controls.Add(this.progressBar3);
            this.Controls.Add(this.progressBar2);
            this.Controls.Add(this.progressBar1);
            this.Controls.Add(this.checkBoxInsertBlank);
            this.Controls.Add(this.textBoxOutput);
            this.Controls.Add(this.textBoxInputAscii);
            this.Controls.Add(this.btnAsciiToHEX);
            this.Name = "Form1";
            this.Text = "跨线程控件通信";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnAsciiToHEX;
        private System.Windows.Forms.TextBox textBoxInputAscii;
        private System.Windows.Forms.TextBox textBoxOutput;
        private System.Windows.Forms.CheckBox checkBoxInsertBlank;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.ProgressBar progressBar2;
        private System.Windows.Forms.ProgressBar progressBar3;
        private System.Windows.Forms.CheckBox checkBoxStart;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
    }
}