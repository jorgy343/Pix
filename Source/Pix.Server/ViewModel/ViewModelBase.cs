using System;
using System.ComponentModel;
using System.Runtime.CompilerServices;

namespace Pix.Server.ViewModel
{
    public abstract class ViewModelBase : INotifyPropertyChanged, IDisposable
    {
        public event PropertyChangedEventHandler PropertyChanged;

        public ViewModelBase(string name = null)
        {
            Name = name;
        }

        public void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        protected virtual void OnDispose()
        {

        }

        public void Dispose()
        {
            OnDispose();
        }

        public string Name { get; }
    }
}