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
    
Finally, we add these 3 components together to get the next steer value, that's the PID control algorithm.
    
    ```
    steer = -tau * cte - tau_d * cte_d - tau_i * integral_cte
    ```

## Hyperparameters Tuning
The most difficult part of this project should be how to choose the 3 factors of P-I-D components (`Kp, Kd, Ki`). I tuned them manually, steps as below:
1. __Kp__: keep the other 2 params(__Ki, Kd__) as zero, first we need to know which value of __Kp__ is probably right. 
    * If it's too small, the car will never reach to the reference/center line, it will be always moving near to the edge or even out of lane in simualtor, you can reach to `p_0.02.mov` to see a video when Kp is too small.   
    * If it's too large, the car's steering value is always bigger than it should be, it oscillates around the center line drastically, that is, the overshooting problem happens at the very beginning, refer to `p_0.2.mov`
    
    After several times of trying, I find out a __Kp__ in range of (0.045, 0.06) should be acceptable.
    
2. __Kd__: despite __Kp__ is fine tuned, it's not enough, the overshooting problem still exists, except that happens later. So we need to tune __kd__ to counteracts the oscillation, a range of (1.4, 1.5) should be fine, refer to `p_0.05_d_1.5.mov`

3. __Ki__: it's basically a parallel shift to the car's track, I tuned this parameter mainly to avoid driving out of the lane edge, a range of (0.0002, 0.0003) should be fine.

Continue tuning these 3 coefficients together to make the car's control more smooth, and more safe, the final result as below
```
pid.Init(0.055, 0.0002, 1.35);
```
