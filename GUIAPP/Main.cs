using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace RFSwitchTestSystem
{
    public partial class Main : Form
    {
        public Main()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (button1.Text == "Open Port")
            {
                serialPort.PortName = comboBox1.SelectedItem.ToString();
                try
                {
                    serialPort.Open();
                    MessageBox.Show("Serial Port " + serialPort.PortName + " Open");
                    button1.Text = "Close Port";
                    if(!radioButton1.Checked)
                    {
                        radioButton1.Checked = true;
                    }
                    radioButton2.Enabled = false;
                    
                }
                catch
                {
                    MessageBox.Show("Unable to open port! Please verify the port number ");
                }
            }
            else
            {
                serialPort.Close();
                button1.Text = "Open Port";
                radioButton2.Enabled = true;
            }
        }

        private void List_Serial_Ports()
        {
            // Get a list of serial port names.
            string[] serialPorts = SerialPort.GetPortNames();

            if (serialPorts.Length > 0)
            {
                // Add it to serial port combo box
                foreach (string port in serialPorts)
                {
                    comboBox1.Items.Add(port);
                }
                comboBox1.SelectedIndex = 0;
            }           
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            List_Serial_Ports();            
        }

        private void button2_Click(object sender, EventArgs e)
        {
            comboBox1.Items.Clear();
            List_Serial_Ports();
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void button4_Click(object sender, EventArgs e)
        {
            listBox1.Items.Add("One");
        }

        private void button10_Click(object sender, EventArgs e)
        {

        }

        public bool TCP_Data_Send(string stringToSend)
        {
            bool returnVal = true;
            string ipaddr = "";
            Int32 port = 0;
            ipaddr = textBox1.Text;
            port = Int32.Parse(textBox2.Text);
            if (ValidateIPv4(ipaddr) == true && port < 9999)
            {
                //Ethernet comm selected
               
                    // Create a TcpClient.
                    // Note, for this client to work you need to have a TcpServer
                    // connected to the same address as specified by the server, port
                    // combination.

                    TcpClient client = new TcpClient();
                try
                {
                    if (!client.ConnectAsync(ipaddr, port).Wait(3000))
                    {
                        // connection failure
                        MessageBox.Show("Failed to connect, please check for device on network");
                        client.Close();
                        returnVal = false;
                    }
                    else
                    {
                        // Translate the passed message into ASCII and store it as a Byte array.
                        Byte[] data = System.Text.Encoding.ASCII.GetBytes(stringToSend);

                        // Get a client stream for reading and writing.
                        //  Stream stream = client.GetStream();

                        NetworkStream stream = client.GetStream();
                        stream.WriteTimeout = 2000;
                        stream.ReadTimeout = 2000;

                        // Send the message to the connected TcpServer.
                        stream.Write(data, 0, data.Length);
                        //listBox2.Items.Add(stringToSend);


                        // Receive the TcpServer.response.

                        // Buffer to store the response bytes.
                        data = new Byte[256];

                        // String to store the response ASCII representation.
                        String responseData = String.Empty;

                        try
                        {
                            // Read the first batch of the TcpServer response bytes.
                            Int32 bytes = stream.Read(data, 0, data.Length);
                            responseData = System.Text.Encoding.ASCII.GetString(data, 0, bytes);
                            //TODO : Add condition to not display useless data
                            listBox1.Items.Add(responseData);
                        }
                        catch
                        {
                            MessageBox.Show("Error in Communcation, Please try again!");
                            returnVal = false;
                        }

                        // Close everything.
                        stream.Close();
                        client.Close();
                    }
                }
                catch
                {
                    MessageBox.Show("Failed to connect, please check for device on network");
                    returnVal = false;
                }
            }
            else
            {
                MessageBox.Show("Please enter valid IP adress and port number");
                returnVal = false;
            }
            return returnVal;
        }
       
        
        public bool RS232_Data_Send(string stringToSend)
        {
            bool returnVal = false;
            if (serialPort.IsOpen)
            {

                try
                {
                    char[] arr = stringToSend.ToCharArray();                    
                    foreach(char c in arr)
                    {
                        char[] a = { '1' };
                        a[0] = c;
                        serialPort.Write(a, 0, 1);
                        Thread.Sleep(10);
                    }
                    returnVal = true;
                }
                catch (System.Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
            else
            {
                MessageBox.Show("Please open the RS232 port");
            }
            return returnVal;
        }


        private void button5_Click(object sender, EventArgs e)
        {
            bool returnVal = false;
            string sentCommandsBox;
            string stringToSend;

            stringToSend = "setinput ";
            stringToSend += numericUpDown1.Value.ToString();
            stringToSend += " ";
            stringToSend += numericUpDown2.Value.ToString();
            stringToSend += '\n';


            if (radioButton1.Checked)
            {
                //RS-232 comm selected               
                returnVal = RS232_Data_Send(stringToSend);
                
            }
            else
            {
                returnVal = TCP_Data_Send(stringToSend);
            }

            if (returnVal)
            {
                sentCommandsBox = "Input ";
                sentCommandsBox += numericUpDown1.Value.ToString();
                sentCommandsBox += " <> ";
                sentCommandsBox += "Output ";
                sentCommandsBox += numericUpDown2.Value.ToString();
                listBox2.Items.Add(sentCommandsBox);
                //Auto scroll down
                int visibleItems = listBox2.ClientSize.Height / listBox2.ItemHeight;
                listBox2.TopIndex = Math.Max(listBox2.Items.Count - visibleItems + 1, 0);
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            bool returnVal = false;
            string sentCommandsBox;
            string stringToSend;
            stringToSend = "setinput ";
            stringToSend += numericUpDown6.Value.ToString();
            stringToSend += " ";
            stringToSend += numericUpDown5.Value.ToString();
            stringToSend += '\n';


            if (radioButton1.Checked)
            {
                //RS-232 comm selected               
                returnVal = RS232_Data_Send(stringToSend);

            }
            else
            {
                returnVal = TCP_Data_Send(stringToSend);
            }

            if (returnVal)
            {
                sentCommandsBox = "Output ";
                sentCommandsBox += numericUpDown6.Value.ToString();
                sentCommandsBox += " <> ";
                sentCommandsBox += "Input ";
                sentCommandsBox += numericUpDown5.Value.ToString();
                listBox2.Items.Add(sentCommandsBox);
                //Auto scroll down
                int visibleItems = listBox2.ClientSize.Height / listBox2.ItemHeight;
                listBox2.TopIndex = Math.Max(listBox2.Items.Count - visibleItems + 1, 0);
            }
        }

        private void button11_Click(object sender, EventArgs e)
        {
            listBox2.Items.Clear();
        }

        private void button12_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
        }

        private bool ValidateIPv4(string ipString)
        {
            if (String.IsNullOrWhiteSpace(ipString))
            {
                return false;
            }

            string[] splitValues = ipString.Split('.');
            if (splitValues.Length != 4)
            {
                return false;
            }

            byte tempForParsing;

            return splitValues.All(r => byte.TryParse(r, out tempForParsing));
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Device_Search newform = new Device_Search();
            newform.Show();          
        }

        private void listBox2_ValueMemberChanged(object sender, EventArgs e)
        {
            //Auto scroll down
            int visibleItems = listBox2.ClientSize.Height / listBox2.ItemHeight;
            listBox2.TopIndex = Math.Max(listBox2.Items.Count - visibleItems + 1, 0);
        }

        delegate void SetTextCallback(string text);

        private void SetText(string text)
        {
            // InvokeRequired required compares the thread ID of the
            // calling thread to the thread ID of the creating thread.
            // If these threads are different, it returns true.
            if (this.listBox1.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(SetText);
                this.Invoke(d, new object[] { text });
            }
            else
            {
                this.listBox1.Items.Add(text);
            }
        }

        private void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;
            string indata = sp.ReadExisting();            
            //MessageBox.Show("Data Received:" + indata);
            
            if(indata.Contains("Set"))
            {
                //MessageBox.Show("Switch operation success");
                SetText("Set");
            }
            else if(indata.Contains("Notset"))
            {
                //MessageBox.Show("Switch operation failed");
                SetText("Not Set");
            }
            else
            {

            }
        }

        private void button4_Click_1(object sender, EventArgs e)
        {
            DeviceConfiguration newform = new DeviceConfiguration(this);
            newform.Show();
        }

        private void button13_Click(object sender, EventArgs e)
        {
            SwitchConfiguration newform = new SwitchConfiguration(this);
            newform.Show();
        }
    }
}
