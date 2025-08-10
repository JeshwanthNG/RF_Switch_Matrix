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
using System.Net;
using System.Net.Sockets;

namespace RFSwitchTestSystem
{

    public partial class Device_Search : Form
    {
        Thread deviceDiscoverTask;
        int PORT = 7;
        UdpClient udpClient;
        IPEndPoint from;            

        private void Device_Discover_Task()
        {
            string rcvStr;          

            while (true)
            {
                var recvBuffer = udpClient.Receive(ref from);
                rcvStr = Encoding.UTF8.GetString(recvBuffer);
                string[] deviceListStr = rcvStr.Split(',');
                if(deviceListStr[0] == "TAD-JES" && deviceListStr.Length == 6)
                {
                    //Ok this is our device
                    BeginInvoke(new Action(() =>
                    {
                        bool updateTable = true;
                        for (int row = 0; row < dataGridView1.RowCount; row++)
                        {
                            string data = (string)dataGridView1[1, row].Value;
                            //If received serial number is already in data table dont put it into 
                            //table
                            if(deviceListStr[2] == data)
                            {
                                updateTable = false;
                                break;
                            }
                        }
                        if(updateTable)
                        {
                            dataGridView1.Rows.Add(deviceListStr.Skip(1).ToArray());
                        }
                    }));                  

                }
            }
        }

       

        public Device_Search()
        {
            InitializeComponent();
            deviceDiscoverTask = new Thread(Device_Discover_Task);
            udpClient = new UdpClient();
            udpClient.Client.Bind(new IPEndPoint(IPAddress.Any, PORT));
            from = new IPEndPoint(0, 0);
        }

        private void BroadCast_Udp_Data()
        {
            var data = Encoding.UTF8.GetBytes("DIS_TA_DEVICES");
            udpClient.Send(data, data.Length, "255.255.255.255", PORT);
        }

        private void button1_Click(object sender, EventArgs e)
        {           
            if (!deviceDiscoverTask.IsAlive)
            {
                deviceDiscoverTask.Start();
            }
            progressBar1.Value = 1;
            progressBar1.Visible = true;
            label1.Visible = true;
            BroadCast_Udp_Data();
            timer1.Enabled = true;
            button1.Enabled = false;
        }

        private void Device_Search_FormClosed(object sender, FormClosedEventArgs e)
        {
            deviceDiscoverTask.Abort();
            udpClient.Client.Close();
            udpClient.Client.Dispose();            
        }
        
        private void timer1_Tick(object sender, EventArgs e)
        {            
            if(progressBar1.Value < 3)
            {
                progressBar1.Value = progressBar1.Value + 1;
                //Send Udp Data Again
                BroadCast_Udp_Data();
            }
            else
            {
                //Done discovering
                progressBar1.Value = 0;
                progressBar1.Visible = false;
                label1.Visible = false;
                button1.Enabled = true;
                timer1.Enabled = false;
                if(dataGridView1.RowCount > 1)
                {
                    MessageBox.Show("Found " + (dataGridView1.RowCount - 1) + " Devices!", "Notification");
                }
                else
                {
                    MessageBox.Show("No Devices Found!" + "\n" + "1. Plese check if the devices are turned on" + "\n" +
                                     "2. Please check if your computer is connected to the device network", "Notification"
                        
                        );
                }
            }
        }

    }
}
