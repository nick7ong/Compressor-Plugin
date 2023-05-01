classdef Compressor
    % Hard Knee Compressor
    properties
        fs
        
        % Envelope Detector Variables
        attackTime
        releaseTime
        
        % Gain Computer Variables
        threshold
        ratio
        
        % DCA and Gain
        gain
        makeupGain
    end
    
    methods
        function obj = Compressor(fs, buffSize, attackTime, releaseTime, threshold, ratio, makeupGain)
            obj.fs = fs;
            
            % Envelope Detector
            obj.attackTime = attackTime; % 5ms
            obj.releaseTime = releaseTime; % 1ms
            
            % Gain Computer
            obj.threshold = threshold;
            obj.ratio = ratio;
            
            % DCA and Gain
            obj.makeupGain = makeupGain;
            obj.gain = zeros(length(buffSize), 1);
        end
        
        function envelopeVals = EnvelopeDetector(obj, inBuffer)
            % Rectify the Input Signal
            rectInput = abs(inBuffer).^2;

            % RC Simulator
            % compute coefficients of filt with on attack and release time
            Tc = log(0.368);
            a0 = Tc/(exp(1)^(obj.fs*obj.attackTime*0.001));
            b1 = Tc/(exp(1)^(obj.fs*obj.releaseTime*0.001));
            rcBuffer = zeros(size(inBuffer));
            forwardValue = 0;
            delayValue = 0;
            
            for i = 1:length(inBuffer)
                forwardValue = a0*(rectInput(i)+ b1*delayValue);
                rcBuffer(i) = rectInput(i) + forwardValue;
                delayValue = rcBuffer(i);
            end

            % logdB Conversion
            envelopeVals = 20*log10(sqrt(rcBuffer));
        end
        
        function obj = GainComputer(obj, envelopeVals)
            dBout = zeros(length(envelopeVals), 1);
            
            for n = 1:length(envelopeVals)
                % Below Knee/Threshold
                if envelopeVals(n) < obj.threshold
                    dBout(n) = envelopeVals(n);
                % Above Knee/Threshold
                elseif envelopeVals(n) > obj.threshold
                    dBout(n) = obj.threshold + (envelopeVals(n) - obj.threshold)/obj.ratio;
                end
            end
            % Convert to lin()
            obj.gain = db2mag(dBout-envelopeVals);
        end
        
        function [obj, yOut] = ProcessBuffer(obj, xIn)
            yOut = zeros(length(xIn), 1);
            envelopeVals = obj.EnvelopeDetector(xIn);
            obj = obj.GainComputer(envelopeVals);
            for n = 1:length(xIn)
                yOut(n) = obj.gain(n) * obj.makeupGain * xIn(n);
            end
        end
    end
end
