using Pix.Server.View;
using Pix.Server.ViewModel;
using System.Windows;

namespace Pix.Server
{
    public partial class App : Application
    {
        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);
            var shell = new ShellView()
            {
                DataContext = new ShellViewModel()
            };

            Current.MainWindow = shell;
            Current.MainWindow.Show();
        }
    }
}