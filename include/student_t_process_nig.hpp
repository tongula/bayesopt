/** \file student_t_process_nig.hpp
    \brief Student's t process with Normal-Inverse-Gamma hyperprior 
    on mean and signal variance parameters. */
/*
-------------------------------------------------------------------------
   This file is part of BayesOpt, an efficient C++ library for 
   Bayesian optimization.

   Copyright (C) 2011-2013 Ruben Martinez-Cantin <rmcantin@unizar.es>
 
   BayesOpt is free software: you can redistribute it and/or modify it 
   under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   BayesOpt is distributed in the hope that it will be useful, but 
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with BayesOpt.  If not, see <http://www.gnu.org/licenses/>.
------------------------------------------------------------------------
*/


#ifndef  _STUDENT_T_PROCESS_NIG_HPP_
#define  _STUDENT_T_PROCESS_NIG_HPP_

#include "student_t_distribution.hpp"
#include "hierarchical_gaussian_process.hpp"

namespace bayesopt
{

  /** \addtogroup  NonParametricProcesses */
  /**@{*/


  /**
   * \brief Student's t process with Normal Inverse-Gamma hyperprior 
   *        on mean and snigal variance parameters.
   */
  class StudentTProcessNIG: public HierarchicalGaussianProcess
  {
  public:
    StudentTProcessNIG(size_t dim, bopt_params params);
    virtual ~StudentTProcessNIG();

    /** 
     * \brief Function that returns the prediction of the GP for a query point
     * in the hypercube [0,1].
     * 
     * @param query in the hypercube [0,1] to evaluate the Gaussian process
     * @return pointer to the probability distribution.
     */	
    ProbabilityDistribution* prediction(const vectord &query);

    double getSignalVariance() { return mSigmaMap; };

  private:

    /** 
     * \brief Computes the negative log likelihood and its gradient of the data.
     * @return value negative log likelihood
     */
    double negativeLogLikelihood();

    /** 
     * \brief Precompute some values of the prediction that do not depends on
     * the query
     * @return error code
     */
    int precomputePrediction();

  private:
    vectord mWMap;                      //!< GP posterior parameters
    double mSigmaMap;                   //!< GP posterior parameters
    double mAlpha, mBeta;
    vectord mW0;
    vectord mInvVarW;
    //! Precomputed GP prediction operations
    vectord mVf;
    matrixd mKF, mD;     

    StudentTDistribution* d_;      //!< Predictive distributions
  };


  /**@}*/

} //namespace bayesopt


#endif
