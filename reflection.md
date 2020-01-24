# Reflection
Generally, I implemented the very basic PID algorithm in this project, tuning the hyperparameters`(Kp, Ki, Kd)` manually, uploaded 4 videos of the car in simulator when I was choosing the P/I/D component.  

## Introduction of P, I, D Components
As the lessons taught us, P-I-D stands for Proportional-Integral-Derivative, these three components combined with the inputs (CTE, timestamps) will output a control signal, 
which is the steer-value in this project.


1. __P component__: In the scenario of control algorithm implementation, we are always given a reference line first, then we can calculate
the CTE(cross track error) at each iteration, that is the distance between the current car location and the reference line. In order to decrease 
the CTE, we calculate a steer value by using a factor `tau` to multiply with CTE, which causes the car to turn __proportional__ to CTE, that's the P component.
Compared to the other 2 components, it has the most directly effect on the car's behavior

    ``` -tau * cte```

2. __D component__: even though P component is important, it's not enough. Using P component alone will cause the car to oscillate around the reference line,
it moves towards the reference line, overshoot to the other side, then revert back to center, overshoot..again and again. To solve this overshooting problem, we
 need an additional D component, that's the __Differential__ component of the controller, which take the derivative of CTE (delta_CTE / delta_t). We also
 introduce a factor `tau_d` to multiply with this derivative to make the car gradually approach the reference line.
    ```
    diff_cte = current_cte - previous_cte
    previous_cte = current_cte
    -tau_d * cte_d
    ```
    
3. __I component__: If there is no systematic bias in the car's control system, then P-D components are enough. The I component is the __integral__ of history errors to deal with systematic biases.
We can imagine if systematic bias is constant, and P-D parameters are both fine tuned, the car's track will always be parallel to the reference line, there is a constant gap all the way.
To solve this problem, we add together all the history CTEs, then multiply it with a factor `tau_i`

    ```
    integral_cte += cte
    -tau_i * integral_cte
    ```
