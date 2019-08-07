using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Windows.Forms;

namespace BuildXL.ShellExtension
{
    static class Program
    {
        [STAThread]
        static void Main(string[] args)
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            MessageBox.Show(StringResources.DoNotRunDirectlyDialog_Instruction, StringResources.WindowTitle,
                MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}
