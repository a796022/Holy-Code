using System;
using Gtk;

namespace wizard
{
    public class KeyboardShortcutManager
    {
        private Window _window;
        private GUI _gui;

        public KeyboardShortcutManager(Window window, GUI gui)
        {
            _window = window;
            _gui = gui;
            SetupDefaultShortcuts();
        }

        private void SetupDefaultShortcuts()
        {
            // Conectamos los eventos de teclado al manejador
            _window.KeyPressEvent += OnKeyPress;
        }

        private void OnKeyPress(object sender, KeyPressEventArgs args)
        {
            // Comprobamos si Control está presionado
            bool isCtrlPressed = (args.Event.State & Gdk.ModifierType.ControlMask) != 0;

            if (isCtrlPressed)
            {
                switch (args.Event.Key)
                {
                    case Gdk.Key.s:
                        OnSave();
                        args.RetVal = true; // Indica que hemos manejado el evento
                        break;

                    case Gdk.Key.o:
                        OnOpen();
                        args.RetVal = true;
                        break;
                }
            }
        }

        private void OnSave()
        {
            _gui.OnSaveMenuItemActivated(null, EventArgs.Empty);
        }

        private void OnOpen()
        {
            _gui.OnOpenMenuItemActivated(null, EventArgs.Empty);
        }

        // Limpia los eventos de teclado cuando se cierra la aplicación
        public void Dispose()
        {
            if (_window != null)
            {
                _window.KeyPressEvent -= OnKeyPress;
            }
        }
    }
}
