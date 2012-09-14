#ifndef OPENSIM_METABOLIC_MUSCLE_H_
#define OPENSIM_METABOLIC_MUSCLE_H_
/* -------------------------------------------------------------------------- *
 *                  OpenSim:  MetabolicMuscleParameter.h                      *
 * -------------------------------------------------------------------------- *
 * The OpenSim API is a toolkit for musculoskeletal modeling and simulation.  *
 * See http://opensim.stanford.edu and the NOTICE file for more information.  *
 * OpenSim is developed at Stanford University and supported by the US        *
 * National Institutes of Health (U54 GM072970, R24 HD065690) and by DARPA    *
 * through the Warrior Web program.                                           *
 *                                                                            *
 * Copyright (c) 2005-2012 Stanford University and the Authors                *
 * Author(s): Tim Dorn                                                        *
 *                                                                            *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may    *
 * not use this file except in compliance with the License. You may obtain a  *
 * copy of the License at http://www.apache.org/licenses/LICENSE-2.0.         *
 *                                                                            *
 * Unless required by applicable law or agreed to in writing, software        *
 * distributed under the License is distributed on an "AS IS" BASIS,          *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied    *
 * See the License for the specific language governing permissions and        *
 * limitations under the License.                                             *
 * -------------------------------------------------------------------------- */

// INCLUDE
#include "Model.h"
#include "Muscle.h"

namespace OpenSim {

//=============================================================================
//                              METABOLIC MUSCLE
//=============================================================================
/**
 * A class for holding the meatbolic properties of a muscle. 
 * The list of current metabolic properties are:
 *
 * - <B>muscle_mass</B> = The mass of the muscle (kg).
 * - <B>ratio_slow_twitch_fibers</B> = Ratio of slow twitch fibers in the muscle (must be between 0 and 1).
 * - <B>activation_constant_slow_twitch</B> = Activation constant for slow twitch fibers (W/kg).
 * - <B>activation_constant_fast_twitch</B> = Activation constant for fast twitch fibers (W/kg).
 * - <B>maintenance_constant_slow_twitch</B> = Maintenance constant for slow twitch fibers (W/kg).
 * - <B>maintenance_constant_fast_twitch</B> = Maintenance constant for slow twitch fibers (W/kg).
 *
 * @author Tim Dorn
 */

//class Model;
//class Muscle;

class OSIMSIMULATION_API MetabolicMuscleParameter : public Object  
{
    OpenSim_DECLARE_CONCRETE_OBJECT(MetabolicMuscleParameter, Object);

//==============================================================================
// PROPERTIES
//==============================================================================
    /** @name Property declarations
    These are the serializable properties associated with this class. **/
    /**@{**/
    OpenSim_DECLARE_PROPERTY(muscle_mass, double,
        "The mass of the muscle (kg).");

    OpenSim_DECLARE_PROPERTY(ratio_slow_twitch_fibers, double,
        "Ratio of slow twitch fibers in the muscle (must be between 0 and 1).");

    OpenSim_DECLARE_PROPERTY(activation_constant_slow_twitch, double,
        "Activation constant for slow twitch fibers (W/kg).");

    OpenSim_DECLARE_PROPERTY(activation_constant_fast_twitch, double,
        "Activation constant for fast twitch fibers (W/kg).");

    OpenSim_DECLARE_PROPERTY(maintenance_constant_slow_twitch, double,
        "Maintenance constant for slow twitch fibers (W/kg).");

    OpenSim_DECLARE_PROPERTY(maintenance_constant_fast_twitch, double,
        "Maintenance constant for fast twitch fibers (W/kg).");
    /**@}**/

//=============================================================================
// DATA
//=============================================================================
protected:

//=============================================================================
// METHODS
//=============================================================================
public:
    //--------------------------------------------------------------------------
    // Constructor(s) and Setup
    //--------------------------------------------------------------------------
    MetabolicMuscleParameter();

    MetabolicMuscleParameter(double muscle_mass, double ratio_slow_twitch_fibers, 
        double activation_constant_slow_twitch, double activation_constant_fast_twitch, 
        double maintenance_constant_slow_twitch, double maintenance_constant_fast_twitch); 

    // Uses default (compiler-generated) destructor, copy constructor, copy 
    // assignment operator.

    //--------------------------------------------------------------------------
    // Get and Set
    //--------------------------------------------------------------------------
    double getMuscleMass() const;
    double getRatioSlowTwitchFibers() const;
    double getActivationConstantSlowTwitch() const;
    double getActivationConstantFastTwitch() const;
    double getMaintenanceConstantSlowTwitch() const;
    double getMaintenanceConstantFastTwitch() const;

    void setMuscleMass(const double aMuscleMass);
    void setRatioSlowTwitchFibers(const double aRatioSlowTwitchFibers);
    void setActivationConstantSlowTwitch(const double aActivationConstantSlowTwitch);
    void setActivationConstantFastTwitch(const double aActivationConstantFastTwitch);
    void setMaintenanceConstantSlowTwitch(const double aMaintenanceSlowTwitch);
    void setMaintenanceConstantFastTwitch(const double aMaintenanceFastTwitch);


private:
    void setNull();
    void constructProperties();

//=============================================================================
};	// END of class MetabolicMuscleParameter
//=============================================================================
//=============================================================================

} // end of namespace OpenSim

#endif // OPENSIM_METABOLIC_MUSCLE_H_