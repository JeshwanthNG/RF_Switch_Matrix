using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace RFSwitchTestSystem
{
    public partial class SwitchConfiguration : Form
    {
        Pen blackPen;        
        int[,] lineLocation = new int[4, 4] {
                    {0, 1, 2, 3} ,   /*  initializers for row indexed by 0 */
                    {4, 5, 6, 7} ,   /*  initializers for row indexed by 1 */
                    {8, 9, 10, 11},   /*  initializers for row indexed by 2 */
                    {8, 9, 10, 11}   /*  initializers for row indexed by 2 */
};
        Button[] inputBtnList;
        Button[] ouputBtnList;
        int[] ouputBtnSwitchNum = new int[4] { 1, 2, 3, 4 };
        public Main mainForm { get; set; }

        public SwitchConfiguration(Main _form1)
        {
            mainForm = _form1;
            blackPen = new Pen(Color.Black, 3);
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Invalidate();
        }

        private void button2_Click(object sender, EventArgs e)
        {

        }

        private void SwitchConfiguration_Load(object sender, EventArgs e)
        {
            inputBtnList = new Button[] { button1, button2, button3, button4 };
            ouputBtnList = new Button[] { button5, button6, button7, button8 };
            //Get all button location to draw linea
            for (int i=0; i<4; i++)
            {
                lineLocation[i, 0] = inputBtnList[i].Location.X + inputBtnList[i].Size.Width;
                lineLocation[i, 1] = inputBtnList[i].Location.Y + inputBtnList[i].Size.Height/2;

                lineLocation[i, 2] = ouputBtnList[i].Location.X;
                lineLocation[i, 3] = ouputBtnList[i].Location.Y + inputBtnList[i].Size.Height / 2;

                ouputBtnSwitchNum[i] = ouputBtnList[i].Text.Last() - '0';

            }
        }

        private void SwitchConfiguration_Paint(object sender, PaintEventArgs e)
        {
            for(int i=0; i<4; i++)
            { 
               e.Graphics.DrawLine(blackPen, lineLocation[i,0], lineLocation[i, 1], lineLocation[i, 2], lineLocation[i, 3]);
            }          
        }

        private void Update_Button_Switch_Number(int btnNum)
        {
            if(ouputBtnSwitchNum[btnNum] < 4)
            {
                //Increment 
                ouputBtnSwitchNum[btnNum]++;
            }
            else
            {
                //Reset to 1
                ouputBtnSwitchNum[btnNum] = 1;
            }
            //Display it on requested button 
            ouputBtnList[btnNum].Text = "OUTPUT-" + ouputBtnSwitchNum[btnNum].ToString();

        }

        private void button5_Click(object sender, EventArgs e)
        {
            Update_Button_Switch_Number(0);
        }

        private void button6_Click(object sender, EventArgs e)
        {
            Update_Button_Switch_Number(1);
        }

        private void button7_Click(object sender, EventArgs e)
        {
            Update_Button_Switch_Number(2);
        }

        private void button8_Click(object sender, EventArgs e)
        {
            Update_Button_Switch_Number(3);
        }

        private bool CheckAllNumDifferent()
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = i + 1; j < 4; j++)
                {                   
                    if (ouputBtnSwitchNum[i] == ouputBtnSwitchNum[j])
                    {
                        return false;
                    }

                }                
            }
            return true;
        }

        private bool sendDataToDevice()
        {
            bool returnVal = false;
            string sentCommandsBox;
            string stringToSend;

            string outSwStates = ouputBtnSwitchNum[0].ToString() +
                                        ouputBtnSwitchNum[1].ToString() +
                                        ouputBtnSwitchNum[2].ToString() +
                                        ouputBtnSwitchNum[3].ToString();
            

            stringToSend = "setinput ";
            stringToSend += outSwStates;
            stringToSend += " ";            
            stringToSend += '\n';            

            if (mainForm.radioButton1.Checked)
            {
                //RS-232 comm selected               
                returnVal = mainForm.RS232_Data_Send(stringToSend);

            }
            else
            {
                returnVal = mainForm.TCP_Data_Send(stringToSend);
            }

            if (returnVal)
            {
                sentCommandsBox = "Input ";
                sentCommandsBox += "1234";
                sentCommandsBox += " <> ";
                sentCommandsBox += "Output ";
                sentCommandsBox += outSwStates;
                mainForm.listBox2.Items.Add(sentCommandsBox);
                //Auto scroll down
                int visibleItems = mainForm.listBox2.ClientSize.Height / mainForm.listBox2.ItemHeight;
                mainForm.listBox2.TopIndex = Math.Max(mainForm.listBox2.Items.Count - visibleItems + 1, 0);
            }

            return returnVal;
        }

        private void button9_Click(object sender, EventArgs e)
        {
            if(CheckAllNumDifferent() == false)
            {
                MessageBox.Show("Invalid Switch Configuration, All Ouputs Must Be Different!","Warning");
            }
            else
            {
                //Send the configuration to device
               
                if(sendDataToDevice() == true)
                {
                    MessageBox.Show("Switch Configuration Send Success!","Notification");
                }                             
            }
        }

        private void SwitchConfiguration_FormClosed(object sender, FormClosedEventArgs e)
        {
            blackPen.Dispose();
        }
    }
}
