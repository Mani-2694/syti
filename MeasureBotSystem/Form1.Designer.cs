namespace MeasureBotSystem
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.StartReceivingButton = new System.Windows.Forms.Button();
            this.StopReceivingButton = new System.Windows.Forms.Button();
            this.GetCurrentValueButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.OpenConnectionButton = new System.Windows.Forms.Button();
            this.CloseConnectionButton = new System.Windows.Forms.Button();
            this.ReceivingMessageBox = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.radioButton1s = new System.Windows.Forms.RadioButton();
            this.label6 = new System.Windows.Forms.Label();
            this.radioButton2s = new System.Windows.Forms.RadioButton();
            this.radioButton3s = new System.Windows.Forms.RadioButton();
            this.radioButton4s = new System.Windows.Forms.RadioButton();
            this.radioButton0s = new System.Windows.Forms.RadioButton();
            this.PHSvalueLabel = new System.Windows.Forms.Label();
            this.SystemStatusValueLabel = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // comboBox1
            // 
            this.comboBox1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new System.Drawing.Point(67, 25);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(150, 23);
            this.comboBox1.TabIndex = 5;
            // 
            // StartReceivingButton
            // 
            this.StartReceivingButton.Cursor = System.Windows.Forms.Cursors.Hand;
            this.StartReceivingButton.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.StartReceivingButton.Location = new System.Drawing.Point(16, 369);
            this.StartReceivingButton.Name = "StartReceivingButton";
            this.StartReceivingButton.Size = new System.Drawing.Size(123, 31);
            this.StartReceivingButton.TabIndex = 0;
            this.StartReceivingButton.Text = "Start Receiving";
            this.StartReceivingButton.UseVisualStyleBackColor = true;
            this.StartReceivingButton.Click += new System.EventHandler(this.StartReceivingButton_Click);
            // 
            // StopReceivingButton
            // 
            this.StopReceivingButton.Cursor = System.Windows.Forms.Cursors.Hand;
            this.StopReceivingButton.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.StopReceivingButton.Location = new System.Drawing.Point(163, 369);
            this.StopReceivingButton.Name = "StopReceivingButton";
            this.StopReceivingButton.Size = new System.Drawing.Size(123, 31);
            this.StopReceivingButton.TabIndex = 1;
            this.StopReceivingButton.Text = "Stop Receiving";
            this.StopReceivingButton.UseVisualStyleBackColor = true;
            this.StopReceivingButton.Click += new System.EventHandler(this.StopReceivingButton_Click);
            // 
            // GetCurrentValueButton
            // 
            this.GetCurrentValueButton.Cursor = System.Windows.Forms.Cursors.Hand;
            this.GetCurrentValueButton.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.GetCurrentValueButton.Location = new System.Drawing.Point(315, 369);
            this.GetCurrentValueButton.Name = "GetCurrentValueButton";
            this.GetCurrentValueButton.Size = new System.Drawing.Size(123, 31);
            this.GetCurrentValueButton.TabIndex = 2;
            this.GetCurrentValueButton.Text = "Get Value";
            this.GetCurrentValueButton.UseVisualStyleBackColor = true;
            this.GetCurrentValueButton.Click += new System.EventHandler(this.GetCurrentValueButton_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Segoe UI", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.label1.ForeColor = System.Drawing.Color.White;
            this.label1.Location = new System.Drawing.Point(564, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(82, 32);
            this.label1.TabIndex = 3;
            this.label1.Text = "Daten";
            // 
            // OpenConnectionButton
            // 
            this.OpenConnectionButton.Cursor = System.Windows.Forms.Cursors.Hand;
            this.OpenConnectionButton.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.OpenConnectionButton.Location = new System.Drawing.Point(252, 22);
            this.OpenConnectionButton.Name = "OpenConnectionButton";
            this.OpenConnectionButton.Size = new System.Drawing.Size(85, 28);
            this.OpenConnectionButton.TabIndex = 6;
            this.OpenConnectionButton.Text = "Open";
            this.OpenConnectionButton.UseVisualStyleBackColor = true;
            this.OpenConnectionButton.Click += new System.EventHandler(this.OpenConnectionButton_Click);
            // 
            // CloseConnectionButton
            // 
            this.CloseConnectionButton.Cursor = System.Windows.Forms.Cursors.Hand;
            this.CloseConnectionButton.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.CloseConnectionButton.Location = new System.Drawing.Point(353, 22);
            this.CloseConnectionButton.Name = "CloseConnectionButton";
            this.CloseConnectionButton.Size = new System.Drawing.Size(85, 28);
            this.CloseConnectionButton.TabIndex = 7;
            this.CloseConnectionButton.Text = "Close";
            this.CloseConnectionButton.UseVisualStyleBackColor = true;
            this.CloseConnectionButton.Click += new System.EventHandler(this.CloseConnectionButton_Click);
            // 
            // ReceivingMessageBox
            // 
            this.ReceivingMessageBox.Enabled = false;
            this.ReceivingMessageBox.Location = new System.Drawing.Point(16, 91);
            this.ReceivingMessageBox.Multiline = true;
            this.ReceivingMessageBox.Name = "ReceivingMessageBox";
            this.ReceivingMessageBox.ReadOnly = true;
            this.ReceivingMessageBox.Size = new System.Drawing.Size(422, 238);
            this.ReceivingMessageBox.TabIndex = 8;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Segoe UI", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.label2.ForeColor = System.Drawing.Color.White;
            this.label2.Location = new System.Drawing.Point(11, 20);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(50, 25);
            this.label2.TabIndex = 4;
            this.label2.Text = "Port:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.label3.ForeColor = System.Drawing.Color.White;
            this.label3.Location = new System.Drawing.Point(12, 65);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(81, 21);
            this.label3.TabIndex = 9;
            this.label3.Text = "Messages:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.label4.ForeColor = System.Drawing.Color.White;
            this.label4.Location = new System.Drawing.Point(583, 54);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(101, 21);
            this.label4.TabIndex = 10;
            this.label4.Text = "Photo-Diode:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.label5.ForeColor = System.Drawing.Color.White;
            this.label5.Location = new System.Drawing.Point(583, 84);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(112, 21);
            this.label5.TabIndex = 11;
            this.label5.Text = "System-Status:";
            // 
            // radioButton1s
            // 
            this.radioButton1s.AutoSize = true;
            this.radioButton1s.ForeColor = System.Drawing.Color.White;
            this.radioButton1s.Location = new System.Drawing.Point(133, 426);
            this.radioButton1s.Name = "radioButton1s";
            this.radioButton1s.Size = new System.Drawing.Size(36, 19);
            this.radioButton1s.TabIndex = 12;
            this.radioButton1s.TabStop = true;
            this.radioButton1s.Text = "1s";
            this.radioButton1s.UseVisualStyleBackColor = true;
            this.radioButton1s.CheckedChanged += new System.EventHandler(this.radioButton1s_CheckedChanged);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.label6.ForeColor = System.Drawing.Color.White;
            this.label6.Location = new System.Drawing.Point(16, 423);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(65, 21);
            this.label6.TabIndex = 13;
            this.label6.Text = "Interval:";
            // 
            // radioButton2s
            // 
            this.radioButton2s.AutoSize = true;
            this.radioButton2s.ForeColor = System.Drawing.Color.White;
            this.radioButton2s.Location = new System.Drawing.Point(175, 426);
            this.radioButton2s.Name = "radioButton2s";
            this.radioButton2s.Size = new System.Drawing.Size(36, 19);
            this.radioButton2s.TabIndex = 14;
            this.radioButton2s.TabStop = true;
            this.radioButton2s.Text = "2s";
            this.radioButton2s.UseVisualStyleBackColor = true;
            // 
            // radioButton3s
            // 
            this.radioButton3s.AutoSize = true;
            this.radioButton3s.ForeColor = System.Drawing.Color.White;
            this.radioButton3s.Location = new System.Drawing.Point(217, 426);
            this.radioButton3s.Name = "radioButton3s";
            this.radioButton3s.Size = new System.Drawing.Size(36, 19);
            this.radioButton3s.TabIndex = 15;
            this.radioButton3s.TabStop = true;
            this.radioButton3s.Text = "3s";
            this.radioButton3s.UseVisualStyleBackColor = true;
            // 
            // radioButton4s
            // 
            this.radioButton4s.AutoSize = true;
            this.radioButton4s.ForeColor = System.Drawing.Color.White;
            this.radioButton4s.Location = new System.Drawing.Point(258, 426);
            this.radioButton4s.Name = "radioButton4s";
            this.radioButton4s.Size = new System.Drawing.Size(36, 19);
            this.radioButton4s.TabIndex = 16;
            this.radioButton4s.TabStop = true;
            this.radioButton4s.Text = "4s";
            this.radioButton4s.UseVisualStyleBackColor = true;
            // 
            // radioButton0s
            // 
            this.radioButton0s.AutoSize = true;
            this.radioButton0s.ForeColor = System.Drawing.Color.White;
            this.radioButton0s.Location = new System.Drawing.Point(91, 426);
            this.radioButton0s.Name = "radioButton0s";
            this.radioButton0s.Size = new System.Drawing.Size(36, 19);
            this.radioButton0s.TabIndex = 17;
            this.radioButton0s.TabStop = true;
            this.radioButton0s.Text = "0s";
            this.radioButton0s.UseVisualStyleBackColor = true;
            // 
            // PHSvalueLabel
            // 
            this.PHSvalueLabel.AutoSize = true;
            this.PHSvalueLabel.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.PHSvalueLabel.ForeColor = System.Drawing.Color.White;
            this.PHSvalueLabel.Location = new System.Drawing.Point(690, 54);
            this.PHSvalueLabel.Name = "PHSvalueLabel";
            this.PHSvalueLabel.Size = new System.Drawing.Size(0, 21);
            this.PHSvalueLabel.TabIndex = 18;
            // 
            // SystemStatusValueLabel
            // 
            this.SystemStatusValueLabel.AutoSize = true;
            this.SystemStatusValueLabel.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.SystemStatusValueLabel.ForeColor = System.Drawing.Color.White;
            this.SystemStatusValueLabel.Location = new System.Drawing.Point(701, 84);
            this.SystemStatusValueLabel.Name = "SystemStatusValueLabel";
            this.SystemStatusValueLabel.Size = new System.Drawing.Size(0, 21);
            this.SystemStatusValueLabel.TabIndex = 19;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.ClientSize = new System.Drawing.Size(978, 478);
            this.Controls.Add(this.SystemStatusValueLabel);
            this.Controls.Add(this.PHSvalueLabel);
            this.Controls.Add(this.radioButton0s);
            this.Controls.Add(this.radioButton4s);
            this.Controls.Add(this.radioButton3s);
            this.Controls.Add(this.radioButton2s);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.radioButton1s);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.ReceivingMessageBox);
            this.Controls.Add(this.CloseConnectionButton);
            this.Controls.Add(this.OpenConnectionButton);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.GetCurrentValueButton);
            this.Controls.Add(this.StopReceivingButton);
            this.Controls.Add(this.StartReceivingButton);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private Button StartReceivingButton;
        private Button StopReceivingButton;
        private Button GetCurrentValueButton;
        private Label label1;
        private ComboBox comboBox1;
        private Button OpenConnectionButton;
        private Button CloseConnectionButton;
        private TextBox ReceivingMessageBox;
        private Label label2;
        private Label label3;
        private Label label4;
        private Label label5;
        private RadioButton radioButton1s;
        private Label label6;
        private RadioButton radioButton2s;
        private RadioButton radioButton3s;
        private RadioButton radioButton4s;
        private RadioButton radioButton0s;
        private Label PHSvalueLabel;
        private Label SystemStatusValueLabel;
    }
}