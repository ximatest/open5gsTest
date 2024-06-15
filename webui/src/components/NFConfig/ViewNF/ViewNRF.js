import {
  NRFSection,
  SBISection,
  LOGSection,
  MaxSection,
  ParameterSection,
  TimeSection,
  MetricsSection,
  CLISection
} from './ViewCfgSection';

export const ViewNRF = ({ nfconfig }) => {
  const {nrf, parameter, max, time } = nfconfig;
  return (
    <div>
      {/* // 使用 LOGSection 组件 */}                  
      <LOGSection nfconfig={nfconfig} />
      {/* // 使用 NRFSection 组件 */}                  
      <NRFSection nfconfig={nfconfig} />
      <div>
        {nrf && (
          <div className="nf-section">
            <MetricsSection metrics={nrf.metrics} />
          </div>
        )}
      </div>
      {/* // 使用 SBISection 组件 */}   
      <SBISection nfconfig={nfconfig} />
      {parameter && <ParameterSection parameter={nfconfig.parameter} />}
      {nfconfig && nfconfig.cli && <CLISection cli={nfconfig.cli} />}
      {/*
      <MaxSection max={max} />
      <TimeSection time={time} />
      */}
    </div>
  );
};