using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace UART
{
    public partial class UART : Form
    {
        public UART()
        {
            InitializeComponent();
        }

        private void btnOpen_Click(object sender, EventArgs e)
        {
            if (!serialPort.IsOpen)
            {
                try
                {
                    serialPort.PortName = tbPortName.Text;
                    int baud;
                    Int32.TryParse(tbBaud.Text, out baud);
                    serialPort.BaudRate = baud;
                    serialPort.Open();
                    btnOpen.Text = "Close";
                    serialPort.DataReceived += new SerialDataReceivedEventHandler(onSerialPortDataRecv);
                }
                catch
                {
                    System.Windows.Forms.MessageBox.Show("Can not open COM port");
                }
            }
            else
            {
                serialPort.Close();
                btnOpen.Text = "Open";
            }
        }

        public void appendRTB(RichTextBox rtb, string text)
        {
            if (this.InvokeRequired)
            {
                this.Invoke(new Action<RichTextBox, string>(appendRTB), new object[] { rtb, text });
            }
            else
            {
                rtb.Text += text;
                rtb.SelectionStart = rtb.Text.Length;
                rtb.Focus();
            }
        }

        private void onSerialPortDataRecv(object sender, SerialDataReceivedEventArgs e)
        {
            try
            {
                appendRTB(rtbRecv, serialPort.ReadExisting());
            }
            catch (Exception exception)
            {
                System.Windows.Forms.MessageBox.Show(exception.Message + "\n\n" + exception.Data);
            }
        }

        private void btnSend_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen) {
                serialPort.Write(tbSend.Text);
            }
        }
    }
}