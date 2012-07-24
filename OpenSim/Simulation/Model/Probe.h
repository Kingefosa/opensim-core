#ifndef OPENSIM_PROBE_H_
#define OPENSIM_PROBE_H_

// Probe.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Tim Dorn
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/* Copyright (c)  2012 Stanford University
* Use of the OpenSim software in source form is permitted provided that the following
* conditions are met:
* 	1. The software is used only for non-commercial research and education. It may not
*     be used in relation to any commercial activity.
* 	2. The software is not distributed or redistributed.  Software distribution is allowed 
*     only through https://simtk.org/home/opensim.
* 	3. Use of the OpenSim software or derivatives must be acknowledged in all publications,
*      presentations, or documents describing work in which OpenSim or derivatives are used.
* 	4. Credits to developers may not be removed from executables
*     created from modifications of the source.
* 	5. Modifications of source code must retain the above copyright notice, this list of
*     conditions and the following disclaimer. 
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
*  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
*  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
*  SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
*  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
*  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*  OR BUSINESS INTERRUPTION) OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
*  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// INCLUDE
#include "Model.h"
#include "ModelComponent.h"

namespace OpenSim {

class Model;

//==============================================================================
//==============================================================================
/**
 * This class represents a Probe which is designed to query a Vector of model values
 * given system state. This model quantity is specified as a SimTK::Vector by the pure
 * virtual method computeProbeInputs(s), which must be specified for each child Probe. 
 * In addition, the Probe model component interface allows <I> operations </I> to be
 * performed on this value (specified by the property: probe_operation), and then have 
 * this result scaled (by the scalar property: 'scale_factor'). 
 * 
 * The data flow of the Probe is shown below:
  \verbatim
 
  ---------------------------
  |  SimTK::Vector          |
  |  computeProbeInputs(s)  |
  ---------------------------
               |
               V
     ---------------------         -------------------------         ----------------------
     |  Query the model  |  ---->  |  Apply the operation  |  ---->  |  Scale the output  |
     |                   |         |   'probe_operation'   |         |   'scale_factor'   |
     ---------------------         -------------------------         ----------------------
                                                                               |
                                                                               V
                                                                    ------------------------
                                                                    |  SimTK::Vector       |
                                                                    |  getProbeOutputs(s)  |
                                                                    ------------------------
  \endverbatim
 * The model query is performed at Stage::Report, so that model values are up to date
 * and is based on the specific Probe's overridden method computeProbeInputs(s). 
 * The final output of the probe is available by accessing getProbeOutputs(s). 
 * Note that all queries, operations, and scaling are performed by SimTK::Measures. 
 * Note also that to define a new child Probe class, two methods which are declared
 * as pure virtual in this Probe abstract class need to be overridden:\n
 * - computeProbeInputs()  ---   returns the input probe values (i.e., model queries).
 * - getNumProbeInputs()   ---   returns the size of the vector of input probe values (i.e., model queries).
 * - getProbeLabels()      ---   returns the labels that correspond to each probe value.
 *
 * <B> Available probe operations: </B>
 * - 'value' (default): returns the probe input value.
 * - 'integrate': returns the integral of the probe input value.
 * - 'differentiate': returns the derivative of the probe input value.
 *
 * The Probe interface differs from the Analysis interface in two fundamental ways:
 * -  (1) Operations can be performed on probes (i.e., in addition to simply reporting 
 *        a model value, model values (probe input values) may have operations performed
 *        on them such as integration and differentiation.
 *
 * -  (2) Analyses are not formally part of the model structure (i.e. they are not 
 *        ModelComponents), and because of this, analysis results can not be accessed with
 *        the model and state value -- they can only be accessed by file at the end of a 
 *        simulation. Probes, on the other hand, are ModelComponents and therefore can be
 *        accessed at any time during a simulation from the API, and can also be used to
 *        compute model values that are fed back into ths system through via custom designed 
 *        Controllers. Note that Probe values can also be reported to file at the end of a
 *        simulation by attaching a ProbeReporter analysis to the simulation.
 *
 *
 * @author Tim Dorn
 */

class OSIMSIMULATION_API Probe : public ModelComponent {
OpenSim_DECLARE_ABSTRACT_OBJECT(Probe, ModelComponent);
public:
//==============================================================================
// PROPERTIES
//==============================================================================
    /** @name Property declarations
    These are the serializable properties associated with this class. **/
    /**@{**/
    /** Enabled by default. **/
    OpenSim_DECLARE_PROPERTY(isDisabled, bool,
        "Flag indicating whether the Probe is disabled or not. Disabled"
        " means that the Probe will not be reported using the ProbeReporter.");

    OpenSim_DECLARE_PROPERTY(probe_operation, std::string,
        "The operation to perform on the probe value: "
        "'value'(no operation, just return the probe value), 'integrate', 'differentiate'");

    OpenSim_DECLARE_OPTIONAL_PROPERTY(initial_conditions_for_integration, SimTK::Vector,
        "Vector of initial conditions to be specified if the 'integrate' operation is "
        "selected. Note that the size of initial conditions must be the same size as "
        "the data being integrated, otherwise an exception will be thrown.");

    OpenSim_DECLARE_PROPERTY(scale_factor, double,
        "Constant value to scale (multiply) the probe output by.");
    /**@}**/

//=============================================================================
// PUBLIC METHODS
//=============================================================================
    Probe();

    // Uses default (compiler-generated) destructor, copy constructor, copy 
    // assignment operator.

    /** Returns true if the Probe is disabled or false if the probe is enabled. */
    bool isDisabled() const;
    /** Set the Probe as disabled (true) or enabled (false). */
    void setDisabled(bool isDisabled);

    /** Return the operation being performed on the probe value. */
    std::string getOperation() const;
    /** Set the operation being performed on the probe value. */
    void setOperation(std::string probe_operation);

    /** Return the initial conditions (when the probe_operation is set to 'integrate'). */
    SimTK::Vector getInitialConditions() const;
    /** Set the initial conditions (when the probe_operation is set to 'integrate'). */
    void setInitialConditions(SimTK::Vector initial_conditions_for_integration);

    /** Return the scale_factor to apply to the probe output. */
    double getScaleFactor() const;
    /** Set the scale_factor to apply to the probe output. */
    void setScaleFactor(double scale_factor);


#ifndef SWIG
    // This is the Probe interface that must be implemented by concrete Probe
    // objects.

    /** Returns the column labels of the Probe values for reporting. 
        This method must be overridden for each subclass Probe to
        provide meaningful names to the probe outputs. 

        @return         The Array<std::string> of Probe labels. **/
    virtual OpenSim::Array<std::string> getProbeLabels() const=0;


    /**Computes the values of the probe inputs prior to any operation being performed.
       This method must be overridden for each subclass Probe.

    @param  state   System state from which value is computed.  
    @return         The SimTK::Vector of Probe input values. **/
    virtual SimTK::Vector computeProbeInputs(const SimTK::State& state) const=0;


    /**Returns the number of probe inputs in the vector returned by computeProbeInputs().
       This method must be overridden for each subclass Probe.

    @param  state   System state from which value is computed.  
    @return         The SimTK::Vector of Probe input values. **/
    virtual int getNumProbeInputs() const=0;
#endif

    /** Returns the values of the probe after the operation has been performed.

    @param  state   System state from which value is computed.  
    @return         The SimTK::Vector of probe output values.**/
    SimTK::Vector getProbeOutputs(const SimTK::State& state) const;

protected:
    // ModelComponent interface.
    /** Concrete probes may override; be sure to invoke Super::connectToModel()
    at the beginning of the overriding method. **/
    void connectToModel(Model& model) OVERRIDE_11;
    /** Concrete probes may override; be sure to invoke Super::addToSystem()
    at the beginning of the overriding method. **/
    void addToSystem(SimTK::MultibodySystem& system) const OVERRIDE_11;


private:
    void setNull();
    void constructProperties();


//=============================================================================
// DATA
//=============================================================================
    //SimTK::Measure_<SimTK::Vector> afterOperationValueVector;
    SimTK::Array_<SimTK::Measure> afterOperationValues;


//=============================================================================
};	// END of class Probe
//=============================================================================
//=============================================================================

} // end of namespace OpenSim

#endif // OPENSIM_PROBE_H_


