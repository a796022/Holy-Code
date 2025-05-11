// Program.cs
using System;

class Program
{
    static void Main(string[] args)
    {
        // 1. Get the data of the operation
        DataBlock[] dataBlocks = DataManager.GetDataBlocks();
        foreach (var block in dataBlocks)
        {
            Console.WriteLine(block);
        }

        // 2. Llamar al planificador para que decida qué acciones tomar con qué bloques de datos
        // ...

        // 3. Llamar al operador para que ejecute las acciones decididas por el planificador
        // 3.1. Para cada operación, el operador construye el bloque de datos oportuno con la información recabada
        // ...

        // 4. Se almacena toda la nueva información recabada
        // ...

        // 5. Se repite el proceso
        // ...
    }
}