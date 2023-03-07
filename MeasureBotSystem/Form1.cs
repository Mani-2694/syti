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

        private void ReadResponse(string response)
        {
            string message = response.Substring(1, response.Length - 2);
            try
            {
                if (message[0] == 'M')
                {
                    string messageData = message.Split("[")[1].Split("]")[0];
                    string[] data = messageData.Split("|");

                    foreach (string item in data)
                    {
                        string data_key = item.Split(":")[0];
                        string data_value = item.Split(":")[1];

                        if (data_key == "photo_voltage")
                        {
                            Invoke(new Action(() => PHSvalueLabel.Text = data_value));
                        }
                        else if (data_key == "switch")
                        {
                            Invoke(new Action(()=>SystemStatusValueLabel.Text = data_value));
                        }
                    }
                }
            }
            catch { }
        }

        private void ReceivedData(object sender, SerialDataReceivedEventArgs e)
        {
            if(CheckIfPortIsOpen())
            {
                string data = "<" + serialPort.ReadTo("<");

                if (data != "<")
                {
                    Invoke(new Action<string>(updateMessageBox), data);
                    ReadResponse(data);
                }
            }

            //string data = serialPort.ReadExisting();
            //do
            //{
            //    data += serialPort.ReadExisting() + "\n";
            //    Invoke(new Action<string>(updateMessageBox), data);
            //}
            //while (!(data.Contains("\x02") && data.Contains("\x03")));
            //{

            //}
        }
        private void updateMessageBox(string data)
        {
            string date = DateTime.Now.ToString("dd.MM.yyyy HH:mm");
            ReceivingMessageBox.AppendText(date + "# " + data + Environment.NewLine);
        }

        private void OpenConnectionButton_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort.PortName = comboBox1.Text;
                serialPort.Open();
                ConnectionStatus.BackColor = Color.Green;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Verbindungsfehler");
            }
        }
        
        private void CloseConnectionButton_Click(object sender, EventArgs e)
        {
            serialPort.Close();
            ConnectionStatus.BackColor = Color.Red;
        }

        private void StartReceivingButton_Click(object sender, EventArgs e)
        {
            SendMessage("<B;t>");
        }

        private void StopReceivingButton_Click(object sender, EventArgs e)
        {
            SendMessage("<B;q>");
        }

        private void GetCurrentValueButton_Click(object sender, EventArgs e)
        {
            SendMessage("<B;a>");
        }

        private bool CheckIfPortIsOpen()
        {
            return serialPort.IsOpen;
        }

        private void SendMessage(string message)
        {
            if(CheckIfPortIsOpen())
                serialPort.WriteLine(message);
        }

        private void SendInterval(int interval)
        {
            SendMessage($"<B;tr{interval}>");
        }

        private void radioButton0s_CheckedChanged(object sender, EventArgs e)
        {
            SendInterval(0);
        }
        private void radioButton1s_CheckedChanged(object sender, EventArgs e)
        {
            SendInterval(1);
        }
        private void radioButton2s_CheckedChanged(object sender, EventArgs e)
        {
            SendInterval(2);
        }
        private void radioButton3s_CheckedChanged(object sender, EventArgs e)
        {
            SendInterval(3);
        }
        private void radioButton4s_CheckedChanged(object sender, EventArgs e)
        {
            SendInterval(4);
        }

        private void ClearMessageBox_Click(object sender, EventArgs e)
        {
            ReceivingMessageBox.Clear();
        }
    }
}