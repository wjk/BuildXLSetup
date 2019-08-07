using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
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

            if (args.Length == 2 && args[0].Equals("/edit", StringComparison.OrdinalIgnoreCase))
            {
                string path = args[1];
                if (File.Exists(path))
                {
                    var startInfo = new ProcessStartInfo(Path.Combine(Environment.SystemDirectory, "notepad.exe"));
                    startInfo.Arguments = $"\"{path}\"";
                    startInfo.UseShellExecute = true;
                    Process.Start(startInfo);
                }
                else
                {
                    string message = string.Format(StringResources.FileNotFoundDialog_Instruction, path);
                    MessageBox.Show(message, StringResources.WindowTitle, MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            else
            {
                MessageBox.Show(StringResources.DoNotRunDirectlyDialog_Instruction, StringResources.WindowTitle,
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}
