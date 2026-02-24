[English](#english) | [Español](#español)

---

## English

# Arduino Simple PID

A clean, from-scratch discrete PID controller template for Arduino.
Built for real embedded control systems, not library wrappers.

### Why build from scratch?

Most Arduino PID libraries abstract away the implementation. This template
exposes every decision so you can understand, tune, and adapt it to your
specific system. It was developed as a foundation for joint control in
robotic systems where understanding the discrete math matters.

### Implementation decisions

**Trapezoidal integration**
The integral term uses the trapezoidal approximation:

```
errorIntegral += (error + errorPrev) / 2.0 * deltaTime
```

This averages the current and previous error before accumulating, which
is more accurate than simple rectangular integration, especially at
lower sampling rates where the error can change significantly between
samples.

**Real elapsed time for derivative**
The derivative uses the actual measured `deltaTime` instead of the fixed
`sampleTime` target. In practice, Arduino loops run slightly late. Using
real elapsed time avoids introducing derivative error from timing jitter.

**Anti-windup**
When the output hits its limits (saturation), the integral stops
accumulating. Without this, the integrator winds up during saturation
and causes overshoot when the system comes back into range. This is
one of the most common failure modes in basic PID implementations.

**Output clamping**
The control signal is clamped to `[outputMin, outputMax]` before being
applied, protecting the actuator from out-of-range commands.

### Usage

1. Set your `setpoint`, `sampleTime`, and output limits
2. Read your sensor into `processVariable` where indicated
3. Write `MV` to your actuator where indicated
4. Tune `Kp`, `Ki`, `Kd` for your system
5. Use Arduino Serial Plotter to monitor all terms in real time

### Tuning guide

Start with all gains at zero. Increase `Kp` until the system oscillates
around the setpoint. Then increase `Ki` slowly to eliminate steady-state
error. Add `Kd` last and keep it small — it amplifies noise.

### Parameters

| Parameter | Description | Default |
|-----------|-------------|---------|
| `sampleTime` | Control loop period (ms) | 300 |
| `setpoint` | Target value | 90 |
| `outputMin` | Lower actuator limit | 0 |
| `outputMax` | Upper actuator limit | 255 |
| `Kp` | Proportional gain | 0.0205 |
| `Ki` | Integral gain | 0.00022 |
| `Kd` | Derivative gain | 0.0 |

### License
MIT

---

## Español

# Arduino PID Simple

Una plantilla limpia de controlador PID discreto para Arduino, implementada
desde cero. Diseñada para sistemas de control embebido reales, no para
envolver librerías existentes.

### ¿Por qué implementarlo desde cero?

La mayoría de las librerías PID para Arduino abstraen la implementación.
Esta plantilla expone cada decisión para que puedas entenderla, ajustarla
y adaptarla a tu sistema específico. Fue desarrollada como base para el
control de articulaciones en sistemas robóticos donde entender la
matemática discreta importa.

### Decisiones de implementación

**Integración trapezoidal**
El término integral usa la aproximación trapezoidal:

```
errorIntegral += (error + errorPrev) / 2.0 * deltaTime
```

Esto promedia el error actual y el anterior antes de acumularlo, lo que
es más preciso que la integración rectangular simple, especialmente a
frecuencias de muestreo bajas donde el error puede cambiar
significativamente entre muestras.

**Tiempo real transcurrido para la derivada**
La derivada usa el `deltaTime` medido realmente, no el `sampleTime` fijo
objetivo. En la práctica, los loops de Arduino se ejecutan con pequeños
retrasos. Usar el tiempo real evita introducir error derivativo por
variaciones en el tiempo de muestreo.

**Anti-windup**
Cuando la salida alcanza sus límites (saturación), la integral deja de
acumularse. Sin esto, el integrador se desborda durante la saturación y
causa sobreimpulso cuando el sistema vuelve al rango normal. Este es uno
de los errores más comunes en implementaciones básicas de PID.

**Limitación de salida**
La señal de control se limita al rango `[outputMin, outputMax]` antes de
aplicarse, protegiendo el actuador de comandos fuera de rango.

### Uso

1. Define tu `setpoint`, `sampleTime` y límites de salida
2. Lee tu sensor en `processVariable` donde se indica
3. Escribe `MV` a tu actuador donde se indica
4. Ajusta `Kp`, `Ki`, `Kd` para tu sistema
5. Usa el Serial Plotter de Arduino para monitorear todos los términos

### Guía de sintonización

Empieza con todas las ganancias en cero. Aumenta `Kp` hasta que el sistema
oscile alrededor del setpoint. Luego aumenta `Ki` lentamente para eliminar
el error en estado estacionario. Agrega `Kd` al final y mantenlo pequeño
— amplifica el ruido.

### Parámetros

| Parámetro | Descripción | Valor por defecto |
|-----------|-------------|-------------------|
| `sampleTime` | Período del loop de control (ms) | 300 |
| `setpoint` | Valor objetivo | 90 |
| `outputMin` | Límite inferior del actuador | 0 |
| `outputMax` | Límite superior del actuador | 255 |
| `Kp` | Ganancia proporcional | 0.0205 |
| `Ki` | Ganancia integral | 0.00022 |
| `Kd` | Ganancia derivativa | 0.0 |

### Licencia
MIT
