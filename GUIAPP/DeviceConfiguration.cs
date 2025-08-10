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
    public partial class DeviceConfiguration : Form
    {
        public Main mainForm { get; set; }

        public DeviceConfiguration(Main _form1)
        {
            mainForm = _form1;
            InitializeComponent();
        }

        private void DeviceConfiguration_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {

        }
    }
}
