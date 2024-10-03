using Gtk;
using System;

class Program
{
    static void Main(string[] args)
    {
        Application.Init();
        
        // Crear la ventana principal
        Window ventana = new Window("Mi ventana GTK");
        ventana.SetDefaultSize(400, 300);
        ventana.DeleteEvent += (sender, e) => Application.Quit();

        // Mostrar la ventana
        ventana.ShowAll();

        // Iniciar el bucle principal de GTK
        Application.Run();
    }
}
