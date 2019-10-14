namespace UART
{
    partial class UART
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
            this.components = new System.ComponentModel.Container();
            this.btnOpen = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.tbPortName = new System.Windows.Forms.TextBox();
            this.tbBaud = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.tbSend = new System.Windows.Forms.TextBox();
            this.btnSend = new System.Windows.Forms.Button();
            this.rtbRecv = new System.Windows.Forms.RichTextBox();
            this.serialPort = new System.IO.Ports.SerialPort(this.components);
            this.SuspendLayout();
            // 
            // btnOpen
            // 
            this.btnOpen.Location = new System.Drawing.Point(195, 12);
            this.btnOpen.Name = "btnOpen";
            this.btnOpen.Size = new System.Drawing.Size(68, 48);
            this.btnOpen.TabIndex = 0;
            this.btnOpen.Text = "Open";
            this.btnOpen.UseVisualStyleBackColor = true;
            this.btnOpen.Click += new System.EventHandler(this.btnOpen_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(7, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(34, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "COM:";
            // 
            // tbPortName
            // 
            this.tbPortName.Location = new System.Drawing.Point(47, 12);
            this.tbPortName.Name = "tbPortName";
            this.tbPortName.Size = new System.Drawing.Size(142, 20);
            this.tbPortName.TabIndex = 2;
            this.tbPortName.Text = "COM1";
            // 
            // tbBaud
            // 
            this.tbBaud.Location = new System.Drawing.Point(47, 38);
            this.tbBaud.Name = "tbBaud";
            this.tbBaud.Size = new System.Drawing.Size(142, 20);
            this.tbBaud.TabIndex = 4;
            this.tbBaud.Text = "115200";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(7, 41);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Baud:";
            // 
            // tbSend
            // 
            this.tbSend.Location = new System.Drawing.Point(12, 64);
            this.tbSend.Name = "tbSend";
            this.tbSend.Size = new System.Drawing.Size(177, 20);
            this.tbSend.TabIndex = 5;
            // 
            // btnSend
            // 
            this.btnSend.Location = new System.Drawing.Point(195, 62);
            this.btnSend.Name = "btnSend";
            this.btnSend.Size = new System.Drawing.Size(68, 23);
            this.btnSend.TabIndex = 6;
            this.btnSend.Text = "Send";
            this.btnSend.UseVisualStyleBackColor = true;
            this.btnSend.Click += new System.EventHandler(this.btnSend_Click);
            // 
            // rtbRecv
            // 
            this.rtbRecv.Location = new System.Drawing.Point(10, 91);
            this.rtbRecv.Name = "rtbRecv";
            this.rtbRecv.Size = new System.Drawing.Size(253, 116);
            this.rtbRecv.TabIndex = 7;
            this.rtbRecv.Text = "";
            // 
            // UART
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(275, 219);
            this.Controls.Add(this.rtbRecv);
            this.Controls.Add(this.btnSend);
            this.Controls.Add(this.tbSend);
            this.Controls.Add(this.tbBaud);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.tbPortName);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btnOpen);
            this.Name = "UART";
            this.Text = "UART";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnOpen;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox tbPortName;
        private System.Windows.Forms.TextBox tbBaud;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox tbSend;
        private System.Windows.Forms.Button btnSend;
        private System.Windows.Forms.RichTextBox rtbRecv;
        private System.IO.Ports.SerialPort serialPort;
    }
}

