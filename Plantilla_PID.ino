

int TiempoMuestreo = 300;        // tiempo de muestreo Se encuentra en milisegundos
unsigned long pasado = 0;      // tiempo pasado (Se hace para asegurar tiempo de muestreo)
unsigned long ahora = 0;			// tiempo que se lleva ejecutando el programa
int CambioTiempo;				//diferencia entre el tiempo actual de ejecucion y el tiempoa anterir de ejecucion para calcular el tiempo de muestreo

int Setpoint = 90;              // referencia 
int VariableProceso = 0			//variable de proceso
int LimiteSuperior = 255;		//limite superir de la señal de salida de control
int LimiteInferir = 0;			//limite inferior de la señal de salida de control

double error = 0;                // error
double errorInt = 0;           //error para la integral
double errorIAnt = 0;         // Suma de errores anteriores para la parte integral  
double errorDer = 0;			// error para la derivada
double errorAnt = 0;			// error anterior

double U = 0;  					// Señal de control limitada en el rango del actuador
double P = 0;                    // control proporcional
double I = 0;                    // control integral
double D = 0;                    // control derivativo 
double MV = 0;					//variable manipulada
double Kp = 0.0205;				//ganancia proporcional
double Ki = 0.00022;			//ganacia integral
double Kd = 0;					//ganancia derivativa



 
void setup()
{

}

void loop() 
{
  ahora = millis();
  CambioTiempo = ahora - pasado;
  
  if(CambioTiempo >= TiempoMuestreo)                    
    {
        error = Setpoint - VariableProceso; 
        errorInt = (((error + errorAnt) / 2) * TiempoMuestreo) + errorIAnt;//probar con CambioTiempo en ves de TiempoMuestreo      
        errorDer = (error - errorAnt) / TiempoMuestreo;// probar con CambioTiempo en ves de TiempoMuestreo
    
        P = Kp * error;                                
        I = Ki * errorInt;                            
        D = Kd * errorDer;
        U = P + I + D;                                            
        
        errorIAnt = errorInt;
        errorAnt = error;
        pasado = ahora;

        MV = constrain(U, LimiteInferir, LimiteSuperior)
    }
}

  
 
