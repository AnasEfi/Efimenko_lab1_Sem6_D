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
using System.Diagnostics;

namespace Efimenko_lab1_Sem6_D
{
    public partial class Form1 : Form
    {
        public int myCounter;
        private Process childProcess = null;
        System.Threading.EventWaitHandle startEvent = new EventWaitHandle(false, EventResetMode.AutoReset, "StartEvent");
        System.Threading.EventWaitHandle stopEvent = new EventWaitHandle(false, EventResetMode.AutoReset, "StopEvent");
        System.Threading.EventWaitHandle confirmEvent = new EventWaitHandle(false, EventResetMode.AutoReset, "ConfirmEvent");
        public Form1()
        {
            InitializeComponent();
        }

        private void StartButton_Click(object sender, EventArgs e)
        {
            if (childProcess == null || childProcess.HasExited) //hasExited- процесс был завершен
            {
                ProcessStartInfo info = new ProcessStartInfo();
                //info.FileName = "Efimenko_lab1_Sem6.exe";
               //info.WorkingDirectory = Environment.CurrentDirectory + "\\..\\..\\..\\..\\Debug";
                childProcess = Process.Start("Efimenko_lab1_Sem6.exe");
                listBox1.Items.Clear();

                listBox1.Items.Add("Threads Count: 0");
                listBox1.Items.Add("Main Thread");

                label2.Text = "0";
                myCounter = 0;
            }
            else
            {
                if (textBox1.Text.Length == 0) return;

                if (int.TryParse(textBox1.Text, out int threadsCounter) == false)
                    return;
                for (int i = 0; i < threadsCounter; i++)
                {
                    startEvent.Set();
                    ++myCounter;
                    label2.Text = myCounter.ToString();
                    confirmEvent.WaitOne();
                    listBox1.Items[0] = "Threads Count: " + myCounter;
                    listBox1.Items.Add("Thread #" + myCounter + " active");
                }
            }

        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (!(childProcess == null || childProcess.HasExited))
            {
                stopEvent.Set();
                confirmEvent.WaitOne();
                --myCounter;
                listBox1.Items.RemoveAt(listBox1.Items.Count - 1);
                if (myCounter >= 0)
                {
                    label2.Text = myCounter.ToString();
                    listBox1.Items[0] = "Threads Count: " + myCounter;
                }
                else
                {
                    label2.Text = "0";
                    //listBox1.Items[0] = "Threads Count: 0";
                }
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if(!(childProcess == null || childProcess.HasExited))
                childProcess.Kill();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
        }
    }
}
