using System;
using System.IO.Ports;

namespace MeasureBotSystem
{
    public partial class Form1 : Form
    {

        public SerialPort serialPort;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            serialPort = new SerialPort { BaudRate = 9600, Parity = Parity.None, DataBits = 8, StopBits = StopBits.One };
            serialPort.DataReceived += ReceivedData;

            string[] ports = SerialPort.GetPortNames();
            comboBox1.Items.AddRange(ports);
            
        }

        private void ReceivedData(object sender, SerialDataReceivedEventArgs e)
        {
            string data = serialPort.ReadExisting();
            do
            {
                data += serialPort.ReadExisting();
            }
            while (!(data.Contains("\x02") && data.Contains("\x03")));
            {
                Invoke(new Action<string>(updateMessageBox), data);
            }
        }
        private void updateMessageBox(string data)
        {
            ReceivingMessageBox.Text = data;
        }
        
        private void OpenConnectionButton_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort.PortName = comboBox1.Text;
                serialPort.Open();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Verbindungsfehler");
            }
        }
        
        private bool CheckIfPortIsOpen()
        {
            return serialPort.IsOpen;
        }

        private void CloseConnectionButton_Click(object sender, EventArgs e)
        {
            serialPort.Close();
        }

        private void StartReceivingButton_Click(object sender, EventArgs e)
        {

        }

        private void StopReceivingButton_Click(object sender, EventArgs e)
        {

        }

        private void GetCurrentValueButton_Click(object sender, EventArgs e)
        {
            serialPort.WriteLine("<<>");
        }

        private void radioButton1s_CheckedChanged(object sender, EventArgs e)
        {
            if (CheckIfPortIsOpen())
            {
                serialPort.Write("1");
            }
        }
    }
}